# STM32智能环境监测系统

## 项目介绍

基于 STM32 + MQTT + Flask + Python 的智能宿舍环境监测系统。

系统实现：
- 温度、湿度、光照、烟雾等环境数据采集
- STM32上传传感器数据
- MQTT实现设备通信
- Python后端数据处理
- Flask Web页面实时展示
- SQLite数据库存储历史数据
- AI模块实现温度预测和异常检测


## 技术栈

### 硬件
- STM32
- 传感器模块

### 软件
- Python
- Flask
- MQTT
- SQLite
- HTML/CSS
- scikit-learn


## 项目结构
SmartDorm
│
├── app.py              # Flask后端
├── mqtt_client.py      # MQTT通信
├── serial_reader.py    # 串口读取
├── database.py         # 数据库操作
├── ai_analysis.py      # AI分析
│
├── templates
│   ├── index.html
│   └── history.html
│
└── static
    └── style.css
    

## 功能展示

### 实时监控
显示当前宿舍环境数据。

### 历史数据
查看温度变化曲线。

### AI分析
- 温度趋势预测
- 异常检测


## 运行方式

安装依赖：
pip install -r requirements.txt

运行：

python app.py


## 项目成员

- 水果物联网：硬件部分
- 六月：软件系统开发
