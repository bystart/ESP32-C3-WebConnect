#include <WiFi.h>          // 引入WiFi库以支持WiFi功能
#include <WebServer.h>     // 引入WebServer库以支持HTTP服务器功能

WebServer server(80);      // 创建一个WebServer对象，监听80端口
const int ledConnected = 12; // 连接状态LED引脚

void setup() {
  Serial.begin(115200);                // 初始化串口通信，波特率为115200
  pinMode(ledConnected, OUTPUT);       // 设置LED引脚为输出模式
  digitalWrite(ledConnected, LOW);     // 初始状态为常灭

  // 创建一个软AP，SSID为"ESP32-C3"，密码为"12345678"
  WiFi.softAP("ESP32-C3", "12345678"); 

  // 设置HTTP请求的处理函数
  server.on("/", HTTP_GET, handleRoot);          // 处理根请求
  server.on("/scan", HTTP_GET, handleScan);      // 处理扫描请求
  server.on("/manual", HTTP_GET, handleManual);   // 处理手动输入请求
  server.on("/set", HTTP_POST, handleSet);        // 处理设置请求
  server.begin();                                 // 启动Web服务器
}

void loop() {
  server.handleClient(); // 处理客户端请求
}

// 处理根请求
void handleRoot() {
  String html = "<html><head><meta charset='UTF-8'></head><body>";
  html += "<h2>WiFi 配网</h2>"; // 显示标题
  html += "<h3>选择配网方式:</h3>"; // 显示选择配网方式的提示
  html += "<button onclick=\"location.href='/scan'\">扫描Wi-Fi信号</button><br>"; // 扫描按钮
  html += "<button onclick=\"location.href='/manual'\">手动输入配网</button><br>"; // 手动输入按钮
  server.send(200, "text/html", html); // 发送HTML响应
}

// 处理扫描请求
void handleScan() {
  String html = "<html><head><meta charset='UTF-8'></head><body>";
  html += "<h2>选择Wi-Fi信号</h2>"; // 显示标题
  html += "<form action=\"/set\" method=\"POST\">"; // 表单开始
  html += "SSID: <select name=\"ssid\">"; // 下拉选择SSID

  // 同步获取SSID列表
  int n = WiFi.scanNetworks(); // 扫描可用的Wi-Fi网络
  String ssidList[20]; // 假设最多有20个SSID
  int ssidCount = 0; // 记录SSID数量

  for (int i = 0; i < n; i++) {
    String currentSSID = WiFi.SSID(i); // 获取当前SSID
    bool isDuplicate = false; // 标记是否重复

    // 检查是否重复
    for (int j = 0; j < ssidCount; j++) {
      if (ssidList[j] == currentSSID) {
        isDuplicate = true; // 如果重复，标记为true
        break;
      }
    }

    // 如果不是重复的SSID，则添加到列表
    if (!isDuplicate) {
      ssidList[ssidCount++] = currentSSID; // 添加到数组
      html += "<option value=\"" + currentSSID + "\">" + currentSSID + "</option>"; // 添加到下拉列表
    }
  }

  html += "</select><br>"; // 结束下拉选择
  html += "Password: <input type=\"password\" name=\"password\" required><br>"; // 密码输入框
  html += "<input type=\"submit\" value=\"连接\">"; // 连接按钮
  html += "</form>"; // 表单结束
  html += "<button onclick=\"location.href='/'\">返回</button>"; // 返回按钮
  html += "</body></html>";
  server.send(200, "text/html", html); // 发送HTML响应
}

// 处理手动输入请求
void handleManual() {
  String html = "<html><head><meta charset='UTF-8'></head><body>";
  html += "<h2>手动输入配网</h2>"; // 显示标题
  html += "<form action=\"/set\" method=\"POST\">"; // 表单开始
  html += "SSID: <input type=\"text\" name=\"ssid\" required><br>"; // SSID输入框
  html += "Password: <input type=\"password\" name=\"password\" required><br>"; // 密码输入框
  html += "<input type=\"submit\" value=\"连接\">"; // 连接按钮
  html += "</form>"; // 表单结束
  html += "<button onclick=\"location.href='/'\">返回</button>"; // 返回按钮
  html += "</body></html>";
  server.send(200, "text/html", html); // 发送HTML响应
}

// 处理设置请求
void handleSet() {
  String ssid = server.arg("ssid"); // 获取SSID
  String password = server.arg("password"); // 获取密码
  WiFi.begin(ssid.c_str(), password.c_str()); // 尝试连接Wi-Fi
  digitalWrite(ledConnected, HIGH); // 连接成功，保持LED常亮
  String html = "<html><head><meta charset='UTF-8'></head><body>";
  html += "连接成功！<br>IP地址: " + WiFi.localIP().toString() + "<br>"; // 显示连接成功信息和IP地址
  html += "<button onclick=\"location.href='/'\">返回首页</button>"; // 返回按钮
  html += "</body></html>";
  server.send(200, "text/html", html); // 发送HTML响应
}


