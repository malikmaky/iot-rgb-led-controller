
![Logo](https://images2.imgbox.com/57/30/HcfWOk7c_o.jpg)



# Remote RGB LED Control via Web Interface [![AGPL License](https://img.shields.io/badge/C/C++-Project-yellow)](https://dotnet.microsoft.com/en-us/languages/csharp) 
    



This project demonstrates the power of IoT (Internet of Things) technology by enabling remote control of an RGB LED via a web interface. Built with an ESP8266 WiFi module and NodeMCU, it allows users to change the color and brightness of the LED from any device connected to the internet.

The implementation utilizes basic concepts of WebSocket, providing full two-way communication. This allows a persistent connection and communication between the web browser (Client) and the server (Server). Through WebSocket, users can send commands to the server to control the RGB LED in real-time and receive immediate feedback. Additionally, the server broadcasts updates to all connected clients, synchronizing the appearance of the current LED color on all pages, ensuring a consistent and interactive user experience.






## Hardware Used :

For this IoT project, several key hardware components were utilized to achieve the remote control functionality of the RGB LED via a web interface. The primary components are the NodeMCU, RGB LED, and resistors.

- #### __NodeMCU :__

The NodeMCU is the core of this project. It is a low-cost open-source IoT platform, based on the ESP8266 WiFi module. The NodeMCU integrates the ESP8266 microcontroller, which has built-in WiFi capabilities, making it ideal for IoT applications.

- #### __RGB LED :__

An RGB LED is a type of LED capable of emitting three different colors of light: red, green, and blue. By adjusting the intensity of each color, a wide range of colors can be produced. In this project, an RGB LED with a cathode (negative) configuration is used. The RGB LED allows users to visually display different colors based on the commands received from the web interface.

- #### __Resistors :__
To ensure the correct operation of the RGB LED and protect it from excessive current, three 330-ohm resistors are used. The resistors limit the current flowing through the LED, preventing damage and ensuring consistent performance.

![Logo](https://images2.imgbox.com/cb/5a/84hpOe4A_o.jpg)



## Libraries Used :

- #### __ESP8266WiFi :__

The *ESP8266WiFi* library is essential for establishing WiFi connectivity with the ESP8266 module. This library allows the NodeMCU to connect to a WiFi network, making it possible to communicate with the web interface over the internet.

- #### __ESP8266WebServer :__

The *ESP8266WebServer* library is used to create a web server on the NodeMCU, allowing it to serve web pages to clients on the network. This library enables the NodeMCU to handle HTTP requests and provide dynamic content, such as the control interface for the RGB LED.

- #### __WebSocketsServer :__

The *WebSocketsServer* library is crucial for implementing real-time communication between the client (web browser) and the server (NodeMCU). WebSockets provide a full-duplex communication channel over a single TCP connection, allowing for instantaneous data exchange.

- #### __ESP8266mDNS :__
The *ESP8266mDNS* ( Multicast DNS ) library is used to create a local DNS server on the NodeMCU, allowing devices on the same network to discover and communicate with each other using simple, human-readable names instead of IP addresses.


## WebSockets & mDNS ( Multicast DNS ) : 

WebSockets provide a communication protocol that enables real-time, full-duplex data exchange between a client and server over a single TCP connection. This persistent connection allows both the client and server to send and receive messages at any time, without the need for repeated HTTP requests. In this project, WebSockets are used to broadcast messages from the server to all connected clients, ensuring that any change in the RGB LED's status is instantly reflected across all devices accessing the web interface. This makes the system highly responsive and interactive, allowing for real-time control and feedback.

mDNS (Multicast DNS) is used to facilitate the discovery of devices on a local network without needing to know their IP addresses. By using mDNS, devices can communicate using simple, human-readable names. In this project, the address FiratIoT.local was used, allowing easy access to the NodeMCU from any device on the same network without needing to remember the specific IP address.

## Lessons Learned :

- __Basics of IoT :__ I learned how to design and develop an IoT system, understanding the fundamental concepts and components involved, such as sensors, actuators, microcontrollers, and communication protocols.

- __WebSockets :__ I discovered how to implement real-time communication between a client and server using WebSockets. This involved understanding how to establish a persistent connection, send and receive messages, and broadcast updates to multiple clients simultaneously.

- __Multicast DNS (mDNS) :__ I learned how to use mDNS to create a local DNS server, allowing devices on the same network to discover each other using simple, human-readable names. This greatly simplified accessing the NodeMCU with the address FiratIoT.local.

- __Programming Languages :__ Despite my initial lack of experience with specific programming languages such as C, C++, HTML, CSS, and JavaScript, I found that writing code in these languages was not as challenging as I had anticipated. My strong foundation in algorithms and familiarity with other programming languages helped me quickly adapt to the syntax and concepts of these new languages.

- __Problem-Solving Skills :__ Working on this project enhanced my problem-solving abilities as I navigated various challenges, from hardware integration to debugging code. This experience reinforced the importance of logical thinking and troubleshooting in developing functional and reliable systems.

- __Web Development :__ Through the creation of the web interface, I improved my understanding of front-end development, learning how to design and implement user-friendly interfaces using HTML, CSS, and JavaScript.

- __Integration of Hardware and Software :__ I gained practical experience in integrating hardware components with software, ensuring seamless communication and control between the NodeMCU, RGB LED, and the web interface.

## Web Interface :
![Logo](https://images2.imgbox.com/db/b6/A59EXdsJ_o.png)
## Credits

This project is maintained by @malikmaky.

For any inquiries or feedback, please contact malikmhmd@hotmail.com

