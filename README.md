# Popsicle
Popsicle��һ�����Qt�ļ��׾���������ͨ�Ź���
���ڶ�����ѧͨ�Ź���רҵ2016���ļ�ѧ������ʵϰ

##��Ҫ����
Popsicle��һ�����Qt�ļ��׾�������ȫͨ�Ź��ߣ����ݼ��ܲ���AES-128-CBC��ʽ���м��ܣ���ԿЭ�̲�����DH��Կ������ͬʱʹ��RSAǩ�����ϰ�ȫ��֧���Զ��û����֣��Ǽ��ܹ������죬����˽�������Լ������ļ����䡣

## ��α��ϰ�ȫ
**~~�Ⲣ����һ�����Ƶ�ͨ��Э�飬ֻ�Ǽ������ڳ�ѧ��Ϣ��ȫ���ʵ�����뷨~~**
����ͨ���ں����ּ��ܼ���ԿЭ�̷����γ���**AES with RSA DH**���ܷ�����
**DH**������ԿЭ�̣�**RSAǩ��**���ڽ��DH�޷�ȷ����ݵ����⣬DHЭ�̳�����Կͨ��MD5�㷨�����32λ16��������ֱ������AES���ܡ�ÿһ��Ӧ�ó���������������DH�㷨�е�X<sub>a</sub>�����仰˵����ÿ��Э�̳���AES��Կ���ǲ�ͬ�ģ�������Կȫ��й¶����ǰ������Ҳ���޷����ܵġ������仰˵����ÿ��Э�̳���AES��Կ���ǲ�ͬ�ģ�������Կȫ��й¶����ǰ������Ҳ���޷����ܵġ�

## ���ù���
 [Qt 5.13.0](https://www.qt.io "Qt 5.13.0")
 [Visual Studio 2019](https://visualstudio.microsoft.com/zh-hans/vs/ "Visual Studio 2019")
 [mpir](http://mpir.org/ "mpir")
 [ReSharper C++](https://www.jetbrains.com/resharper-cpp/ "ReSharper C++")

## �ο�����
[JieweiWei/md5](https://github.com/JieweiWei/md5 "JieweiWei/md5") ��md5�㷨
[Liu233w/natchat](https://github.com/Liu233w/natchat "Liu233w/natchat") ����ֲ����ģ��
[lowbees/WindowsFramelessWindowHelper](https://github.com/lowbees/WindowsFramelessWindowHelper "lowbees/WindowsFramelessWindowHelper") ��Qt�ޱߴ���
[laserpants/qt-material-widgets](https://github.com/laserpants/qt-material-widgets "laserpants/qt-material-widgets") ��Qt Material �������

## ��������ע������
�״α������ȱ���components
����ͨ��vcpkgΪVS��װmpir
DH��Կ��RSA��Կ������Ӧ�ó���ͬ��Ŀ¼������Ϊdh.key��rsa.key
**˫��ͨ����Ҫ��ͬ��dh.key**
Ӧ�ó�����Ҫdh.key����������������û�п��ȱ�������DH Generator���ɣ�rsa��Կ����ʱ�Զ����ɻ���Ӧ���ڸ���

##δ��
**~~��̫���ܼ������£���Ҫ��������⻹��Ҫ�г���~~**
������Windows API���������Ǩ�Ƶ�QtNetwork���Ա��ڶ�ƽ̨ʹ��
�ļ����ͽ�����д��Ϊ�˱���һЩ�޷���������Ⲣû����ƽ���ǰ��ȷ�ϻ���
������ƽ����Լ������߼�
�����������߰����signal��slot