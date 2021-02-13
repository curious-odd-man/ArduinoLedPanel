# Overview

Code to control LED strip using ESP8266 module.

# NOTE:

This project is currently in development.

# Features:

1. Over the Air updates. See [ArduinoOtaWrapper](main/src/ota/ArduinoOtaWrapper.cpp)
1. Connect to existing router or act as an Access Point. See [WiFiWrapper](main/src/svc/WiFiWrapper.cpp)
1. Web UI. See [WebServer](main/src/svc/WebServer.cpp)
1. Prometheus + Grafana metrics. See [Monitorin](monitoring) for setup in docker and [MetricsCollector](main/src/metrics/MetricsCollector.cpp) class.
1. Protection against broken software. See [Safguard class](main/src/svc/Safeguard.cpp)

# My setup

1. [ESP-01](https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/ESP-01.jpg/300px-ESP-01.jpg) module
1. [WS2812B](https://blog.seeedstudio.com/wp-content/uploads/2019/02/Featured-Pic-2-1-1030x515.png) Led strip

# Project structure

