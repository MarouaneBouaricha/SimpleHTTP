# SimpleHTTP
A simple implementation of a HTTP server in the C language
## Description
- The server has only one default file to show (index.html) 
- It check the existing of the file
- Check if the client has the permisson to read
- give the right status code for the situations above
## Requirement
- The server use **Unix** sys calls so it **must** run on a **Linux/Unix** machine like
## Usage
```
> gcc server.c -o server
> ./server
```

## Output
```
+++++++ Waiting for new connection ++++++++

```
## Client (web browser)
- <localhost/machine-addrIp>:8080
![index.html file](https://github.com/MarouaneBouaricha/SimpleHTTP/blob/master/Capture.PNG)
