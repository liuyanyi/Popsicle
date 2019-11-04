# Popsicle
Popsicle是一款基于Qt的简易局域网加密通信工具

用于东北大学通信工程专业2016级夏季学期生产实习

## 主要功能
Popsicle是一款基于Qt的简易局域网安全通信工具，内容加密采用AES-128-CBC格式进行加密，密钥协商采用了DH密钥交换，同时使用RSA签名保障安全。支持自动用户发现，非加密公屏聊天，加密私密聊天以及加密文件传输。

## 如何保障安全

**~~这并不是一个完善的通信协议，只是几个人在初学信息安全后的实验性想法~~**

我们通过融合三种加密及密钥协商方案形成了**AES with RSA DH**加密方案。

**DH**用于密钥协商，**RSA签名**用于解决DH无法确认身份的问题，DH协商出的密钥通过MD5算法计算出32位16进制数，直接用于AES加密。每一次应用程序启动都会重置DH算法中的X<sub>a</sub>，换句话说就是每次协商出的AES密钥都是不同的，即便密钥全部泄露，以前的数据也是无法解密的。，换句话说就是每次协商出的AES密钥都是不同的，即便密钥全部泄露，以前的数据也是无法解密的。

## 所用工具
 [Qt 5.13.0](https://www.qt.io "Qt 5.13.0")
 [Visual Studio 2019](https://visualstudio.microsoft.com/zh-hans/vs/ "Visual Studio 2019")
 [mpir](http://mpir.org/ "mpir")
 [ReSharper C++](https://www.jetbrains.com/resharper-cpp/ "ReSharper C++")

## 参考代码
[JieweiWei/md5](https://github.com/JieweiWei/md5 "JieweiWei/md5") ：md5算法
[Liu233w/natchat](https://github.com/Liu233w/natchat "Liu233w/natchat") ：移植网络模块
[lowbees/WindowsFramelessWindowHelper](https://github.com/lowbees/WindowsFramelessWindowHelper "lowbees/WindowsFramelessWindowHelper") ：Qt无边窗口
[laserpants/qt-material-widgets](https://github.com/laserpants/qt-material-widgets "laserpants/qt-material-widgets") ：Qt Material 界面组件

## 编译运行注意事项
首次编译请先编译components
建议通过vcpkg为VS安装mpir
DH密钥和RSA密钥储存在应用程序同级目录，命名为dh.key和rsa.key
**双方通信需要相同的dh.key**
应用程序需要dh.key才能正常启动，如没有可先编译运行DH Generator生成，rsa密钥启动时自动生成或在应用内更新

## 未来

**~~不太可能继续更新，但要解决的问题还是要列出来~~**

将基于Windows API的网络组件迁移到QtNetwork，以便于多平台使用
文件发送接收重写，为了避免一些无法解决的问题并没有设计接收前的确认环节
重新设计界面以及各类逻辑
修正各种乱七八糟的signal和slot
