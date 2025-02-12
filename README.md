# 🔒 Secure TLS/SSL Client-Server Communication  

## 📖 Overview  

This project implements a **secure client-server communication system** using **TLS/SSL encryption** in **C**. The system consists of a **client** and a **server**, which communicate over a secure connection, ensuring **data confidentiality and integrity**.  

The client sends a **numeric input** to the server, and the server processes the input by **incrementing the number** and sending it back. This simple computation serves as a demonstration of encrypted communication between two networked entities.  

---

## 🛠 Technologies Used  

- **C Programming** – Core implementation of the client and server.  
- **OpenSSL** – TLS/SSL encryption for secure communication.  
- **POSIX Sockets** – Used for network communication.  
- **Linux Networking APIs** – For handling TCP connections.  

---

## 📌 Features  

✅ **TLS/SSL Encryption** – Ensures secure communication between the client and server.  
✅ **Client-Server Model** – Implements a simple request-response architecture.  
✅ **Input Processing** – Client sends a number, and the server increments it before sending it back.  
✅ **Error Handling** – Handles connection failures and invalid inputs gracefully.  
✅ **Secure Certificate Handling** – Uses self-signed certificates for authentication.  

---

## 🚀 How It Works  

1️⃣ The **server** starts, listens on a port, and waits for client connections.  
2️⃣ The **client** connects to the server and establishes a secure TLS/SSL session.  
3️⃣ The client **sends a number**, which the server **increments** and sends back.  
4️⃣ Communication continues until the client decides to **exit**.  

---

## 📂 Project Structure  

```
📁 Secure-TLS-Client-Server/
│── client.c             # Client implementation
│── server.c             # Server implementation
│── client.key           # Client private key
│── client.crt           # Client certificate
│── server.key           # Server private key
│── server.crt           # Server certificate
│── self_signed_client.crt  # Self-signed certificate for the client
│── self_signed_server.crt  # Self-signed certificate for the server
│── README.md            # Project documentation
```

---

## 🛠 Setup & Compilation  

### 🔹 **Compiling the Server**  
```sh
gcc -o server server.c -lssl -lcrypto
```

### 🔹 **Compiling the Client**  
```sh
gcc -o client client.c -lssl -lcrypto
```

---

## 🏃 Running the Application  

### 1️⃣ **Start the Server**  
```sh
./server <port> <authentication_mode> <private_key> [certificate]
```

Example:  
```sh
./server 4433 strict server.key server.crt
```

### 2️⃣ **Run the Client**  
```sh
./client <port>
```

Example:  
```sh
./client 4433
```

Once connected, the client can send **numeric inputs** to the server, and the server will **increment** them before sending them back.

---

## 🔐 Certificates & Security  

- The server and client communicate using **self-signed certificates** (`server.crt` & `client.crt`).  
- **OpenSSL** is used to establish **TLS/SSL encryption**.  
- Server authentication is required to **validate certificates** before communication.  

To generate new **self-signed certificates**, use:  

```sh
openssl req -x509 -newkey rsa:4096 -keyout server.key -out server.crt -days 365 -nodes
openssl req -x509 -newkey rsa:4096 -keyout client.key -out client.crt -days 365 -nodes
```

---

## 🔮 Future Enhancements  

🔹 **Mutual Authentication** – Enforce both client and server certificate validation.  
🔹 **Better Error Handling** – Improve user-friendly error messages.  
🔹 **Support for Multiple Clients** – Enhance server to handle concurrent connections.  
🔹 **Logging & Debugging** – Implement structured logs for debugging and monitoring.  

---

## 📜 References  

- [OpenSSL Documentation](https://www.openssl.org/docs/)  
- [Linux Socket Programming](https://beej.us/guide/bgnet/)  
- [TLS/SSL Networking Guide](https://www.feistyduck.com/books/openssl-cookbook/)  

---

## 📧 Contact  

**Author:** Siddartha Reddy Boreddy  
📍 **SUNY Binghamton**  
✉️ **Email:** sboreddy@binghamton.edu  

---

### ⭐ If you find this project helpful, feel free to star the repository! 🚀  
