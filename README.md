# ESP32 Wi-Fi 配网案例

## 项目简介
该项目使用ESP32开发板实现Wi-Fi配网功能。用户可以通过Web界面扫描附近的Wi-Fi信号或手动输入Wi-Fi SSID和密码进行连接。

## 功能
- **扫描Wi-Fi信号**：用户可以扫描附近的Wi-Fi信号，并从下拉列表中选择一个SSID进行连接。
- **手动输入配网**：用户可以手动输入Wi-Fi的SSID和密码进行连接。

## 硬件要求
- ESP32开发板

## 软件要求
- Arduino IDE
- ESP32开发板支持库

## 使用说明
1. 上传代码后，ESP32将创建一个Wi-Fi热点，SSID为`ESP32-C3`，密码为`12345678`。
2. 连接到该热点后，打开浏览器并访问`http://192.168.4.1`。
3. 在Web界面中，选择“扫描Wi-Fi信号”以查看可用的Wi-Fi网络，或选择“手动输入配网”以手动输入SSID和密码。
4. 点击“连接”按钮进行连接。
