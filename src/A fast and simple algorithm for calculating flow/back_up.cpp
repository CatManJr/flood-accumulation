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
////#define DEM_SIZE 100		//sizeҪС�ڵ���dem���ݵĳ��Ϳ����Բ���vector�����洢���ݣ������Ը�ǿ
//const int NODATA = -9999;
//std::vector<std::vector<float>> getMatrix(string path)
//{
//    // ʹ��GDAL��TIFF�ļ�
//    GDALAllRegister();//ע�����е�����
//    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //����֧������·�����ļ���
//
//    //1������tif����
//    string file_path_name = path;
//
//    GDALDataset* poDataset = (GDALDataset*)GDALOpen(file_path_name.c_str(), GA_ReadOnly);//GA_Update��GA_ReadOnly����ģʽ
//    if (poDataset == NULL)
//    {
//        std::cout << "��ȡդ�����ʧ�ܣ�" << endl;
//        return {};
//    }
//
//    // ��ȡդ�������������
//    int nRows = poDataset->GetRasterYSize();
//    int nCols = poDataset->GetRasterXSize();
//
//    // ����һ����ά�������洢DEM��ֵ
//    std::vector<std::vector<float>> DEM_init(nRows, std::vector<float>(nCols));
//
//    // ��ȡ��һ������
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//
//    // ��ȡ����
//    for (int i = 0; i < nRows; ++i) {
//        poBand->RasterIO(GF_Read, 0, i, nCols, 1, &DEM_init[i][0], nCols, 1, GDT_Float32, 0, 0);
//    }
//
//    // ��ȡNoDataֵ
//    int success;
//    double NoDataValue = poBand->GetNoDataValue(&success);
//    if (success)
//        std::cout << "NoDataֵΪ��" << NoDataValue << endl;
//    {
//        // �������NoDataֵ���������鲢����NoDataֵ
//        for (int i = 0; i < nRows; ++i) {
//            for (int j = 0; j < nCols; ++j) {
//                if (DEM_init[i][j] == NoDataValue) {
//                    // ��NoDataֵ�滻Ϊ-9999
//                    DEM_init[i][j] = -9999;
//                }
//            }
//        }
//    }
//    // ����߽�
//    int top = 0, bottom = nRows - 1, left = 0, right = nCols - 1;
//
//    while (true) {
//        bool foundNoData = false;
//
//        // ������ǰ�ı߽�
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
//        // ����ڵ�ǰ�ı߽����ҵ���NoDataֵ����ô���߽�������Сһ��
//        if (foundNoData) {
//            ++top; --bottom; ++left; --right;
//        }
//        else {
//            // ����ڵ�ǰ�ı߽���û���ҵ�NoDataֵ����ô����ѭ��
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
//    // �ر����ݼ�
//    GDALClose(poDataset);
//    std::cout << "��ȡդ�����ɹ���" << endl;
//    //����DEM
//    return DEM_final;
//}
//
//// ����һ��ϸ���ṹ��װ��DEM�е�Ԫ��
//struct Cell {
//    int row, col;
//    float dem;
//    bool operator<(const Cell& rhs) const {
//        return dem > rhs.dem;  // ���ȼ�������Ҫ��С��
//    }
//};
//
////ʹ����ˮ��ʵ������(Olivier Planchon & Frederic Darboux, 2002)
//std::vector<std::vector<float>> Fill(const std::vector<std::vector<float>>& DEM) {
//    int rows = DEM.size();
//    int cols = DEM[0].size();
//    // ����������άvector�ҵ����ֵ
//    int max_val = DEM[0][0];  // ��ʼ��Ϊ��һ�е�һ�е�ֵ
//    for (const auto& row : DEM) {
//        for (int val : row) {
//            if (val > max_val) {
//                max_val = val;
//            }
//        }
//    }
//
//    //��ʼ�� Fill������ˮ��
//    std::vector<std::vector<float>> Fill(rows, std::vector<float>(cols, max_val + 1));
//    //����˸������neighbour
//    std::vector<std::pair<int, int>> directions = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
//
//    //�����߽��Nodataԭʼֵ
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1 || DEM[i][j] == -9999) {
//                Fill[i][j] = DEM[i][j];
//            }
//        }
//    }
//
//    //����ˮ
//    bool Fill_done = false;
//    while (!Fill_done) {
//        Fill_done = true;
//        //�����߽�
//        for (int i = 1; i < rows - 1; ++i) {
//            for (int j = 1; j < cols - 1; ++j) {
//                //�ҵ����ܵ��ݵ�
//                if (Fill[i][j] > DEM[i][j]) {
//                    for (const auto& dir : directions) {
//                        int newRow = i + dir.first;
//                        int newCol = j + dir.second;
//                        //�߽�����
//                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && DEM[newRow][newCol] != -9999) {
//                            //ȷ���г��ڵ�����£���֤Fill �ƽ� DEM
//                            if (DEM[i][j] > DEM[newRow][newCol] + 0.0001) {
//                                Fill[i][j] = DEM[i][j];
//                                Fill_done = false;
//                                break;
//                            }
//                            //���û����֪�ĳ��ڣ�����ˮ��֤������һ������
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
//    // �����ް���Fill����
//    return Fill;
//}
//
////�򻯵�D8�㷨ʵ�ֵ�������㣨�����ǻ�����������أ�
//std::vector<std::vector<int>> d8_Algorithm(const std::vector<std::vector<float>>& fill) {
//    int rows = fill.size();
//    int cols = fill[0].size();
//
//    std::vector<std::vector<int>> flowDirection(rows, std::vector<int>(cols, 0));
//
//    // ���巽���ѯ��  
//    std::vector<std::vector<int>> dir = { {8, 16, 32}, {4, 0, 64}, {2, 1, 128} };
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            float z = fill[i][j];
//            if (z == -9999) {  // դ��ֵΪ-9999������Ϊ0
//                flowDirection[i][j] = 0;
//                continue;
//            }
//
//            //��ʼ�������������ж�����
//            float down_slope = 0;
//            int min_dir = 0;
//
//            // �������8���ھ�,�����¿�ʼ����
//            for (int di = -1; di <= 1; ++di) {
//                for (int dj = -1; dj <= 1; ++dj) {
//                    int ni = i + di;
//                    int nj = j + dj;
//
//                    // �������ĵ�Ԫ���û���ھӵķ���
//                    if ((di == 0 && dj == 0) || ni < 0 || ni >= rows || nj < 0 || nj >= cols) continue;
//
//                    //�Խ��߷���ˮƽ����Ϊ����2�����෽��ˮƽ����Ϊ1
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
//                        // ����ھӵ�DEMֵ�뵱ǰ��Ԫ����ͬ���ھӵ�����Ϊ0��������ָ���ھ�
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
//            //���ش�����Ӧ������
//            flowDirection[i][j] = min_dir;
//        }
//    }
//
//    return flowDirection;
//}
////ʵ�ֱ���DEM��Cell�ĺ���
//Cell NextCell(Cell c, vector<vector<int>>& FlowDir) {
//    // ����8�������ƫ����
//    std::vector<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
//    std::vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };
//
//    // ����8�������ֵ
//    std::vector<int> d8 = { 16, 32, 64, 128, 1, 2, 4, 8 };
//
//    // ���ÿ������
//    for (int k = 0; k < 8; ++k) {
//        // ��� c ��Ԫ����������������
//        if (FlowDir[c.row][c.col] == d8[k]) {
//            // �������ε�Ԫ���λ��
//            int newRow = c.row + dx[k];
//            int newCol = c.col + dy[k];
//
//            // ������ε�Ԫ���Ƿ��� DEM �ķ�Χ��
//            if (newRow >= 0 && newRow < FlowDir.size() && newCol >= 0 && newCol < FlowDir[0].size() && FlowDir[newRow][newCol] != -9999) {
//                // �������ε�Ԫ�������Ϊ FlowDir ����Ӧλ�õ�ֵ
//                return { newRow, newCol, static_cast<float>(FlowDir[newRow][newCol]) };
//            }
//            else {
//                return { -1, -1, -1 };  // �����к���Ϊ-1��ʾû�����ε�Ԫ��
//            }
//        }
//    }
//
//    // ��� c ��Ԫ����������κ�һ�����򣬷���һ������� Cell ���������б�
//    return { -1, -1, -1 };  // �����к���Ϊ-1��ʾû�����ε�Ԫ��
//}
//
////��ʼ��NIDP(��עԴϸ���ͽ���ϸ�����ڲ�ϸ��)
//vector<vector<int>> initialize_NIDP(vector<vector<int>>& FlowDir) {
//    // ��ȡ FlowDir ������������
//    int rows = FlowDir.size();
//    int cols = FlowDir[0].size();
//
//    // ����һ���µ� NIDP ���󣬳�ʼ��Ϊ��
//    vector<vector<int>> NIDP(rows, vector<int>(cols, 0));
//
//    // ����8�������ƫ����
//    std::vector<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
//    std::vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };
//    std::vector<int> d8 = { 1, 2, 4, 8,16, 32, 64, 128 };
//
//    // ����ÿһ����Ԫ��;
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            // ���ÿ�������ϵ��ھ�
//            for (int k = 0; k < 8; ++k) {
//                int ni = i + dx[k];
//                int nj = j + dy[k];
//
//                // ����ھ��Ƿ��� DEM �ķ�Χ��
//                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
//                    // ����ھӵ�����ָ��ǰ��Ԫ������ NIDP ֵ��NIDP>1������ϸ����0����Դϸ����1�����ڲ�ϸ��
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
////����NIDP��ͼ�������ۼ�����ģ�ⷨ��Zhou et al., 2017��
//std::vector<vector<int>> Accumulate(std::vector<vector<int>>& FlowDir) {
//    // ��ȡ FlowDir ������������
//    int rows = FlowDir.size();
//    int cols = FlowDir[0].size();
//
//    // ����һ���µĶ�ά���� FlowAccu������Ԫ�س�ʼ��Ϊ1
//    vector<vector<int>> FlowAccu(rows, vector<int>(cols, 1));
//
//    // ���� initialize_NIDP
//    vector<vector<int>> NIDP = initialize_NIDP(FlowDir);
//
//    // ����ÿһ����Ԫ��
//    for (int row = 0; row < FlowDir.size(); ++row) {
//        for (int col = 0; col < FlowDir[0].size(); ++col) {
//            Cell c = { row, col , FlowDir[row][col] };
//            if (NIDP[row][col] != 0) continue;
//            Cell n = c;
//            int nAccu = 0;
//            do {
//                FlowAccu[n.row][n.col] += nAccu;
//                nAccu = FlowAccu[n.row][n.col];
//                //����ϸ���ѱ����ʹ�һ�Σ�NIDP-1
//                if (NIDP[n.row][n.col] > 1) {
//                    NIDP[n.row][n.col]--;
//                    break;
//                }
//                //�����α���
//                n = NextCell(n, FlowDir);
//            } while (n.row != -1 && n.row < rows
//                && n.col != -1 && n.col < cols);//ֱ��������������DEM��Χ
//        }
//    }
//    return FlowAccu;
//}
//
////д��TIFF�ļ��ļ�
//void writetif(const std::vector<std::vector<int>>& FlowAccu)
//{
//    // ʹ��GDALд��TIFF�ļ�
//    GDALAllRegister();//ע�����е�����
//    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //����֧������·�����ļ���
//    //��������
//    GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
//    if (poDriver == NULL)
//    {
//        std::cout << "��ȡ����ʧ�ܣ�" << endl;
//        return;
//    }
//    //�������ݼ�
//    //string output_file = "C:\\Users\\23962\\Desktop\\test1\\result\\streamTMS.tif";
//    string output_file;
//    std::cout << "�������������ݵ����·����";
//    cin >> output_file;
//    std::cout << "�������ݵ����·����" << output_file << endl;
//    GDALDataset* poDataset = poDriver->Create(output_file.c_str(), FlowAccu[0].size(), FlowAccu.size(), 1, GDT_Float32, NULL);
//    if (poDataset == NULL)
//    {
//        std::cout << "�������ݼ�ʧ�ܣ�" << endl;
//        return;
//    }
//    //д������
//    int nCols = poDataset->GetRasterXSize();
//    int nRows = poDataset->GetRasterYSize();
//    float* pData = new float[nCols * nRows];
//    for (int i = 0; i < nRows; ++i) {
//        for (int j = 0; j < nCols; ++j)
//        {
//            pData[i * nCols + j] = FlowAccu[i][j];
//        }
//    }
//    //�������ݼ��Ĳ���
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//    poBand->RasterIO(GF_Write, 0, 0, nCols, nRows, pData, nCols, nRows, GDT_Float32, 0, 0);
//    //�ͷ��ڴ�
//    delete[]pData;
//    pData = NULL;
//    //�ر����ݼ�
//    GDALClose((GDALDatasetH)poDataset);
//    return;
//}
//
////����һ�����������ߣ�ʵ�����п��ӻ�
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
////main����ִ���㷨
//void main()
//{
//    // ��ȡDEM����
//    //string file_path = "C:\\Users\\23962\\Desktop\\test1\\tms.tif";
//    //string file_path = "C:\\Users\\23962\\Desktop\\TEST\\test\\clip_1.tif";
//    string file_path;
//    std::cout << "������DEM���ݵ�·����";
//    cin >> file_path;
//    std::vector<std::vector<float>> DEM = getMatrix(file_path);
//
//    printProgress(1, 6);
//
//    //����DEM�е��ݵ�
//    std::vector<std::vector<float>> Spill = Fill(DEM);
//    //for (int i = 0; i < Spill.size(); ++i) {
//    //    for (int j = 0; j < Spill[i].size(); ++j) {
//    //        std::cout << Spill[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    std::cout << "�����ݵز�������ɣ�" << endl;
//
//    printProgress(2, 6);
//    //����D8�㷨����DEM�ĵ�����
//    std::vector<std::vector<int>> d8_DEM = d8_Algorithm(Spill);
//    //for (int i = 0; i < d8_DEM.size(); ++i) {
//    //    for (int j = 0; j < d8_DEM[i].size(); ++j) {
//    //        std::cout << d8_DEM[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    printProgress(4, 6);
//    std::cout << "����DEM�ĵ�������ɣ�" << endl;
//
//    // ����DEM���ۻ�����
//    std::vector<std::vector<int>> FlowAccu = Accumulate(d8_DEM);
//    //for (int i = 0; i < FlowAccu.size(); ++i) {
//    //    for (int j = 0; j < FlowAccu[i].size(); ++j) {
//    //        std::cout << FlowAccu[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//    printProgress(5, 6);
//
//    //д������
//    writetif(FlowAccu);
//    std::cout << "д������������ɣ�" << endl;
//    printProgress(6, 6);
//    return;
//}