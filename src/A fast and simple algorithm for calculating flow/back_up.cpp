//#include <iostream>
//#include <gdal_priv.h>
//
//#include <fstream>
//#include <vector>
//#include <queue>
//#include <algorithm>
//#include <set>
//#include <sstream>
//#include <ctime>
//#include <cmath>
//using namespace std;
////#define DEM_SIZE 100		//size要小于等于dem数据的长和宽，可以采用vector容器存储数据，复用性更强
//const int NODATA = -9999;
//std::vector<std::vector<float>> getMatrix(string path)
//{
//    // 使用GDAL打开TIFF文件
//    GDALAllRegister();//注册所有的驱动
//    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //设置支持中文路径和文件名
//
//    //1、加载tif数据
//    string file_path_name = path;
//
//    GDALDataset* poDataset = (GDALDataset*)GDALOpen(file_path_name.c_str(), GA_ReadOnly);//GA_Update和GA_ReadOnly两种模式
//    if (poDataset == NULL)
//    {
//        std::cout << "获取栅格矩阵失败！" << endl;
//        return {};
//    }
//
//    // 获取栅格的行数和列数
//    int nRows = poDataset->GetRasterYSize();
//    int nCols = poDataset->GetRasterXSize();
//
//    // 创建一个二维向量来存储DEM的值
//    std::vector<std::vector<float>> DEM_init(nRows, std::vector<float>(nCols));
//
//    // 获取第一个波段
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//
//    // 读取数据
//    for (int i = 0; i < nRows; ++i) {
//        poBand->RasterIO(GF_Read, 0, i, nCols, 1, &DEM_init[i][0], nCols, 1, GDT_Float32, 0, 0);
//    }
//
//    // 获取NoData值
//    int success;
//    double NoDataValue = poBand->GetNoDataValue(&success);
//    if (success)
//        std::cout << "NoData值为：" << NoDataValue << endl;
//    {
//        // 如果存在NoData值，遍历数组并处理NoData值
//        for (int i = 0; i < nRows; ++i) {
//            for (int j = 0; j < nCols; ++j) {
//                if (DEM_init[i][j] == NoDataValue) {
//                    // 将NoData值替换为-9999
//                    DEM_init[i][j] = -9999;
//                }
//            }
//        }
//    }
//    // 定义边界
//    int top = 0, bottom = nRows - 1, left = 0, right = nCols - 1;
//
//    while (true) {
//        bool foundNoData = false;
//
//        // 遍历当前的边界
//        for (int i = top; i <= bottom; ++i) {
//            for (int j = left; j <= right; ++j) {
//                if (i == top || i == bottom || j == left || j == right) {
//                    if (DEM_init[i][j] == -9999) {
//                        foundNoData = true;
//                        break;
//                    }
//                }
//            }
//            if (foundNoData) break;
//        }
//
//        // 如果在当前的边界上找到了NoData值，那么将边界向内缩小一格
//        if (foundNoData) {
//            ++top; --bottom; ++left; --right;
//        }
//        else {
//            // 如果在当前的边界上没有找到NoData值，那么结束循环
//            break;
//        }
//    }
//
//    std::vector<std::vector<float>> DEM_final(bottom - top + 1, std::vector<float>(right - left + 1));
//
//    for (int i = top; i <= bottom; ++i) {
//        for (int j = left; j <= right; ++j) {
//            DEM_final[i - top][j - left] = DEM_init[i][j];
//        }
//    }
//
//
//    // 关闭数据集
//    GDALClose(poDataset);
//    std::cout << "获取栅格矩阵成功！" << endl;
//    //返回DEM
//    return DEM_final;
//}
//
//// 定义一个细胞结构体装载DEM中的元素
//struct Cell {
//    int row, col;
//    float dem;
//    bool operator<(const Cell& rhs) const {
//        return dem > rhs.dem;  // 优先级队列需要最小堆
//    }
//};
//
////使用排水法实现填洼(Olivier Planchon & Frederic Darboux, 2002)
//std::vector<std::vector<float>> Fill(const std::vector<std::vector<float>>& DEM) {
//    int rows = DEM.size();
//    int cols = DEM[0].size();
//    // 遍历整个二维vector找到最大值
//    int max_val = DEM[0][0];  // 初始化为第一行第一列的值
//    for (const auto& row : DEM) {
//        for (int val : row) {
//            if (val > max_val) {
//                max_val = val;
//            }
//        }
//    }
//
//    //初始化 Fill矩阵（淹水）
//    std::vector<std::vector<float>> Fill(rows, std::vector<float>(cols, max_val + 1));
//    //定义八个方向的neighbour
//    std::vector<std::pair<int, int>> directions = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
//
//    //保留边界和Nodata原始值
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1 || DEM[i][j] == -9999) {
//                Fill[i][j] = DEM[i][j];
//            }
//        }
//    }
//
//    //逐步排水
//    bool Fill_done = false;
//    while (!Fill_done) {
//        Fill_done = true;
//        //跳过边界
//        for (int i = 1; i < rows - 1; ++i) {
//            for (int j = 1; j < cols - 1; ++j) {
//                //找到可能的洼地
//                if (Fill[i][j] > DEM[i][j]) {
//                    for (const auto& dir : directions) {
//                        int newRow = i + dir.first;
//                        int newCol = j + dir.second;
//                        //边界问题
//                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && DEM[newRow][newCol] != -9999) {
//                            //确保有出口的情况下，保证Fill 逼近 DEM
//                            if (DEM[i][j] > DEM[newRow][newCol] + 0.0001) {
//                                Fill[i][j] = DEM[i][j];
//                                Fill_done = false;
//                                break;
//                            }
//                            //如果没有已知的出口，逐渐排水保证至少有一个出口
//                            if (Fill[i][j] > Fill[newRow][newCol] + 1) {
//                                Fill[i][j] = Fill[newRow][newCol] + 1;
//                                Fill_done = false;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // 返回无凹陷Fill矩阵
//    return Fill;
//}
//
////简化的D8算法实现单流向计算（不考虑汇和连续开阔地）
//std::vector<std::vector<int>> d8_Algorithm(const std::vector<std::vector<float>>& fill) {
//    int rows = fill.size();
//    int cols = fill[0].size();
//
//    std::vector<std::vector<int>> flowDirection(rows, std::vector<int>(cols, 0));
//
//    // 定义方向查询表  
//    std::vector<std::vector<int>> dir = { {8, 16, 32}, {4, 0, 64}, {2, 1, 128} };
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            float z = fill[i][j];
//            if (z == -9999) {  // 栅格值为-9999的流向赋为0
//                flowDirection[i][j] = 0;
//                continue;
//            }
//
//            //初始化溢流和流向判断条件
//            float down_slope = 0;
//            int min_dir = 0;
//
//            // 检查所有8个邻居,从左下开始遍历
//            for (int di = -1; di <= 1; ++di) {
//                for (int dj = -1; dj <= 1; ++dj) {
//                    int ni = i + di;
//                    int nj = j + dj;
//
//                    // 跳过中心单元格和没有邻居的方向
//                    if ((di == 0 && dj == 0) || ni < 0 || ni >= rows || nj < 0 || nj >= cols) continue;
//
//                    //对角线方向水平距离为根号2，其余方向水平距离为1
//                    if ((di == -1 && dj == -1) || (di == -1 && dj == 1) || (di == 1 && dj == -1) || (di == 1 && dj == 1))
//                    {
//                        if (fill[ni][nj] == -9999) continue;
//                        float slope = (fill[ni][nj] - fill[i][j]) / 1.414;
//                        if (slope < down_slope) {
//                            down_slope = slope;
//                            min_dir = dir[di + 1][dj + 1];
//                        }
//                    }
//                    else if (fill[ni][nj] - fill[i][j] == 0 && flowDirection[ni][nj] != 0) {
//                        // 如果邻居的DEM值与当前单元格相同且邻居的流向不为0，则流向指向邻居
//                        down_slope = 0;
//                        min_dir = dir[di + 1][dj + 1];
//                    }
//                    else
//                    {
//                        if (fill[ni][nj] == -9999) continue;
//                        float slope = fill[ni][nj] - fill[i][j];
//                        if (slope < down_slope) {
//                            down_slope = slope;
//                            min_dir = dir[di + 1][dj + 1];
//                        }
//                    }
//                }
//            }
//            //返回大落差对应的流向
//            flowDirection[i][j] = min_dir;
//        }
//    }
//
//    return flowDirection;
//}
////实现遍历DEM中Cell的函数
//Cell NextCell(Cell c, vector<vector<int>>& FlowDir) {
//    // 定义8个方向的偏移量
//    std::vector<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
//    std::vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };
//
//    // 定义8个方向的值
//    std::vector<int> d8 = { 16, 32, 64, 128, 1, 2, 4, 8 };
//
//    // 检查每个方向
//    for (int k = 0; k < 8; ++k) {
//        // 如果 c 单元格的流向是这个方向
//        if (FlowDir[c.row][c.col] == d8[k]) {
//            // 计算下游单元格的位置
//            int newRow = c.row + dx[k];
//            int newCol = c.col + dy[k];
//
//            // 检查下游单元格是否在 DEM 的范围内
//            if (newRow >= 0 && newRow < FlowDir.size() && newCol >= 0 && newCol < FlowDir[0].size() && FlowDir[newRow][newCol] != -9999) {
//                // 返回下游单元格，溢出量为 FlowDir 中相应位置的值
//                return { newRow, newCol, static_cast<float>(FlowDir[newRow][newCol]) };
//            }
//            else {
//                return { -1, -1, -1 };  // 假设行和列为-1表示没有下游单元格
//            }
//        }
//    }
//
//    // 如果 c 单元格的流向不是任何一个方向，返回一个特殊的 Cell 对象用于判别
//    return { -1, -1, -1 };  // 假设行和列为-1表示没有下游单元格
//}
//
////初始化NIDP(标注源细胞和交叉细胞和内部细胞)
//vector<vector<int>> initialize_NIDP(vector<vector<int>>& FlowDir) {
//    // 获取 FlowDir 的行数和列数
//    int rows = FlowDir.size();
//    int cols = FlowDir[0].size();
//
//    // 创建一个新的 NIDP 矩阵，初始化为零
//    vector<vector<int>> NIDP(rows, vector<int>(cols, 0));
//
//    // 定义8个方向的偏移量
//    std::vector<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
//    std::vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };
//    std::vector<int> d8 = { 1, 2, 4, 8,16, 32, 64, 128 };
//
//    // 遍历每一个单元格;
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            // 检查每个方向上的邻居
//            for (int k = 0; k < 8; ++k) {
//                int ni = i + dx[k];
//                int nj = j + dy[k];
//
//                // 检查邻居是否在 DEM 的范围内
//                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
//                    // 如果邻居的流向指向当前单元格，增加 NIDP 值，NIDP>1代表交叉细胞，0代表源细胞，1代表内部细胞
//                    if (FlowDir[ni][nj] == d8[k]) {
//                        NIDP[i][j]++;
//                    }
//                }
//            }
//        }
//    }
//
//    return NIDP;
//}
//
////基于NIDP和图遍历的累计流量模拟法（Zhou et al., 2017）
//std::vector<vector<int>> Accumulate(std::vector<vector<int>>& FlowDir) {
//    // 获取 FlowDir 的行数和列数
//    int rows = FlowDir.size();
//    int cols = FlowDir[0].size();
//
//    // 创建一个新的二维数组 FlowAccu，所有元素初始化为1
//    vector<vector<int>> FlowAccu(rows, vector<int>(cols, 1));
//
//    // 调用 initialize_NIDP
//    vector<vector<int>> NIDP = initialize_NIDP(FlowDir);
//
//    // 遍历每一个单元格
//    for (int row = 0; row < FlowDir.size(); ++row) {
//        for (int col = 0; col < FlowDir[0].size(); ++col) {
//            Cell c = { row, col , FlowDir[row][col] };
//            if (NIDP[row][col] != 0) continue;
//            Cell n = c;
//            int nAccu = 0;
//            do {
//                FlowAccu[n.row][n.col] += nAccu;
//                nAccu = FlowAccu[n.row][n.col];
//                //交叉细胞已被访问过一次，NIDP-1
//                if (NIDP[n.row][n.col] > 1) {
//                    NIDP[n.row][n.col]--;
//                    break;
//                }
//                //向下游遍历
//                n = NextCell(n, FlowDir);
//            } while (n.row != -1 && n.row < rows
//                && n.col != -1 && n.col < cols);//直到这条流线流出DEM范围
//        }
//    }
//    return FlowAccu;
//}
//
////写入TIFF文件文件
//void writetif(const std::vector<std::vector<int>>& FlowAccu)
//{
//    // 使用GDAL写入TIFF文件
//    GDALAllRegister();//注册所有的驱动
//    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //设置支持中文路径和文件名
//    //创建驱动
//    GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
//    if (poDriver == NULL)
//    {
//        std::cout << "获取驱动失败！" << endl;
//        return;
//    }
//    //创建数据集
//    //string output_file = "C:\\Users\\23962\\Desktop\\test1\\result\\streamTMS.tif";
//    string output_file;
//    std::cout << "请输入流量数据的输出路径：";
//    cin >> output_file;
//    std::cout << "流量数据的输出路径：" << output_file << endl;
//    GDALDataset* poDataset = poDriver->Create(output_file.c_str(), FlowAccu[0].size(), FlowAccu.size(), 1, GDT_Float32, NULL);
//    if (poDataset == NULL)
//    {
//        std::cout << "创建数据集失败！" << endl;
//        return;
//    }
//    //写入数据
//    int nCols = poDataset->GetRasterXSize();
//    int nRows = poDataset->GetRasterYSize();
//    float* pData = new float[nCols * nRows];
//    for (int i = 0; i < nRows; ++i) {
//        for (int j = 0; j < nCols; ++j)
//        {
//            pData[i * nCols + j] = FlowAccu[i][j];
//        }
//    }
//    //设置数据集的波段
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//    poBand->RasterIO(GF_Write, 0, 0, nCols, nRows, pData, nCols, nRows, GDT_Float32, 0, 0);
//    //释放内存
//    delete[]pData;
//    pData = NULL;
//    //关闭数据集
//    GDALClose((GDALDatasetH)poDataset);
//    return;
//}
//
////创建一个进度条工具，实现运行可视化
//void printProgress(int progress, int total)
//{
//    int barWidth = 70;
//
//    std::cout << "[";
//    int pos = barWidth * progress / total;
//    for (int i = 0; i < barWidth; ++i) {
//        if (i < pos) std::cout << "=";
//        else if (i == pos) std::cout << ">";
//        else std::cout << " ";
//    }
//    std::cout << "] " << int(progress * 100.0 / total) << " %\r" << endl;
//    std::cout.flush();
//}
//
//
////main函数执行算法
//void main()
//{
//    // 读取DEM数据
//    //string file_path = "C:\\Users\\23962\\Desktop\\test1\\tms.tif";
//    //string file_path = "C:\\Users\\23962\\Desktop\\TEST\\test\\clip_1.tif";
//    string file_path;
//    std::cout << "请输入DEM数据的路径：";
//    cin >> file_path;
//    std::vector<std::vector<float>> DEM = getMatrix(file_path);
//
//    printProgress(1, 6);
//
//    //搜索DEM中的洼地
//    std::vector<std::vector<float>> Spill = Fill(DEM);
//    //for (int i = 0; i < Spill.size(); ++i) {
//    //    for (int j = 0; j < Spill[i].size(); ++j) {
//    //        std::cout << Spill[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    std::cout << "搜索洼地并填洼完成！" << endl;
//
//    printProgress(2, 6);
//    //利用D8算法计算DEM的单流向
//    std::vector<std::vector<int>> d8_DEM = d8_Algorithm(Spill);
//    //for (int i = 0; i < d8_DEM.size(); ++i) {
//    //    for (int j = 0; j < d8_DEM[i].size(); ++j) {
//    //        std::cout << d8_DEM[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    printProgress(4, 6);
//    std::cout << "计算DEM的单流向完成！" << endl;
//
//    // 计算DEM的累积流量
//    std::vector<std::vector<int>> FlowAccu = Accumulate(d8_DEM);
//    //for (int i = 0; i < FlowAccu.size(); ++i) {
//    //    for (int j = 0; j < FlowAccu[i].size(); ++j) {
//    //        std::cout << FlowAccu[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    printProgress(5, 6);
//
//    //写入数据
//    writetif(FlowAccu);
//    std::cout << "写入流量数据完成！" << endl;
//    printProgress(6, 6);
//    return;
//}