# Flood-Accumulation

## Course Work for 2023 Fall *Develop a GIS from bottom up*
## English
### Overview
This repository contains the course work for *Develop a GIS from bottom up*, focusing on flood accumulation calculations. It has been developed using C++20 standards and is designed to be compiled and run in Visual Studio 2022 Community X64 debug mode.  
It can process a 696-line, 493-column 32-bit DEM dataset on a single thread on a laptop Intel i7-13700HX 2100MHz chip with no more than 6s, 23MB memory.

### Getting Started

1. **Solution Compilation**
   - The `src` folder contains the complete project solution `.sln` file.
   - Compile and run the solution after compiling it. It has been successfully compiled and tested in Visual Studio 2022 Community X64 debug mode.

2. **Algorithm and Logic**
   - The `presentation.pdf` document provides a detailed explanation of the algorithms and logic implemented in the code.

3. **Data Sets**
   - The `dataset` folder contains two example DEM (Digital Elevation Model) data sets, each with a scale of 1e6.
   - The `Test result` folder contains the data results after running the solution. You could extract the streams and visualize them more beautifully using ArcGIS.

4. **Software Requirements**
   - **GDAL 3.X Library**: To run this solution, you need to compile the GDAL 3.X library locally.
   - **IDE Compatibility**: You can use any C/C++ compatible IDE to open and compile this file.
   - **Compiler Standard**: Please ensure your compiler supports C++20 standards（maybe no need. I cannot remember whether I had used C++20 API OvO）.

5. **Additional Materiel**
   - The `Fill.txt` file contains a small component `std::vector<vector<float>> Fill`, which implements a depression filling method using a priority queue with a time complexity of O(n).
   - Note: This method has a memory management issue and has not been merged into the final solution. But I considered it elegant and, therefore, it was finally retained (^ v ^).
## 中文
### 概述
此仓库是一个专注于高速洪水累积量计算的 *地理信息系统底层开发* 作业。使用C++20标准开发，并在Visual Studio 2022 Community X64 Debug模式下编译和运行通过。在笔记本Intel i7-13700HX 2100MHz芯片上单线程处理一个696行，
493列，32 Bit的DEM数据只需要不超过6s，23MB内存。

### 开始使用

1. **解决方案编译**
   - `src` 文件夹包含了完整的项目解决方案 `.sln` 文件。
   - 编译后运行解决方案。它已在Visual Studio 2022 Community X64调试模式下成功编译和测试。

2. **算法和逻辑**
   - `presentation.pdf` 文档提供了代码中实现的算法和逻辑的详细说明。

3. **数据集**
   - `dataset` 文件夹包含了两个示例的DEM（数字高程模型）数据集，数据集的尺寸大约为1e6个像素。
   - `Test result` 文件夹包含了运行解决方案后的数据结果。你可以在ArcGIS中进一步提取流线和可视化。

4. **软件要求**
   - **GDAL 3.X库**：要运行此解决方案，您需要在本地编译GDAL 3.X库。
   - **IDE兼容性**：您可以使用任何兼容C/C++的IDE打开和编译此文件。
   - **编译器标准**：请确保您的编译器支持C++20标准（其实不用，我感觉我都没怎么用20的特性 OvO）。

5. **额外材料**
   - `Fill.txt` 文件包含了一个函数 `std::vector<vector<float>> Fill`，它使用优先队列实现了一种填洼方法，时间复杂度为O(n)。
   - 注意：该方法存在内存管理问题于是没有在项目中部署，但我认为这种方法非常优雅，因此保留了txt版本(^ v ^)。

### References

1. Zhou, G., Wei, H., & Fu, S. (2019). A fast and simple algorithm for calculating flow accumulation matrices from raster digital elevation. *Frontiers of Earth Science: English Edition*, 13(2), 10.
2. Planchon, O., & Frédéric Darboux. (2002). A fast, simple, and versatile algorithm to fill the depressions of digital elevation models. *Catena*, 46(2-3), 159-176.
3. Wang, L., & Liu, H. (2006). An efficient method for identifying and filling surface depressions in digital elevation models for hydrologic analysis and modeling. *International Journal of Geographical Information Science*.

---
How to compile GDAL 3.X for local C++？  
[GDAL with Visual Studio 2022](https://kantlee.blog.csdn.net/article/details/130292595?fromshare=blogdetail&sharetype=blogdetail&sharerId=130292595&sharerefer=PC&sharesource=Blue_Yuki10086&sharefrom=from_link)
