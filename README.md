# gravyweb
An HTTP web server implementation with support for HTTPS.

# Disclaimer
I am not an authority in the field of web servers. This project is just for fun and educational purposes, so use at your own discretion.

# Features
- HTTP request parsing
- HTTP to HTTPS forwarding
- Simple mechanism to create routes and controllers for different request methods
- Easy to use HTTP response creation

# Dependencies
You're only required to install OpenSSL development libraries. I have developed this project on Linux so I can't say what exactly is required to make it work on Windows. In theory you need to link with OpenSSL and ws2_32 (Winsock2) if you want to try this. If you want to have support for HTTPS, you need to provide a certicate. To generate a self signed certificate use following command `openssl req -newkey rsa:4096 -x509 -sha256 -days 3650 -nodes -out cert.pem -keyout key.pem`. After creating a certificate, be sure to update the settings in config.txt.