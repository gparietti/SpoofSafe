# SpoofSafe

This project demonstrates how easily a simple ESP8266 can create a fake Wi-Fi network (spoofing) that mimics a real one and tricks users into entering sensitive credentials. The goal is to raise awareness about recognizing insecure connections and protecting personal data.

------------------------------------------------------------------------------
# ⚠️ DISCLAIMER!!!

The author is not responsible for any misuse of this project, including but not limited to phishing or any other malicious activities.  
This project is intended solely for educational and ethical purposes to raise awareness about Wi-Fi security risks.
It shows how to create a realistic login portal to highlight cybersecurity risks in public WiFi networks.

------------------------------------------------------------------------------

 # ⚠️ WARNINGS:
  1. Do NOT use this code for illegal activities or phishing
  2. Use ONLY in controlled environments with explicit authorization
  3. The author assumes no responsibility for misuse of this code
  4. This project demonstrates how credentials can be easily compromised
     on insecure networks, emphasizing the importance of:
     - Always verifying WiFi network legitimacy
     - Using HTTPS connections
     - Avoiding public WiFi for sensitive operations

------------------------------------------------------------------------------
## 📚 Libraries Used

This project uses the following libraries for ESP8266 development:

- `DNSServer.h`  
  Provides DNS server capabilities used to redirect all DNS requests to the captive portal.

- `ESP8266WebServer.h`  
  Implements the web server to serve web pages and handle HTTP requests from clients.

- `ESP8266WiFi.h`  
  Enables Wi-Fi functions, including creating an access point and managing connections.

------------------------------------------------------------------------------
# MIT License

Copyright (c) [2025] [Gabriele Parietti]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
