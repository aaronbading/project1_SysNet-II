# project1_SysNet-II HTTP SERVER

# Http Server
This is a custom Http server created to aid our understanding in the Http protocol and socket programming. 
This project seemed straightforward and simple; however, it did involve a good bit of learning.  

## How to use
### Compilation 
After compiling the program inside on your local machine  by entering the command "**make**" into the terminal, you can run then the server by entering the command "**./startserver**".
This server is great proof of concept because it functions just like any other server. It receives requests, handles them, and continues to listen. 
### Making Requests
Upon starting the server we will be seeing the requests come in and the relevant information is displayed in the terminal. Once its started, go ahead and open up your favorite browser and type "**localhost:60049**" into the search bar. This will then display the default page which will have a few links to try out.    
### The links
Once we see the default page there will be three links going to index.html, testPresence.html and notfound.html.
index.html is synonymous to the default page, testPresence.html displays a cool image and notfound.html will display a 404 not found code. 
In addition, if there is any unknown link typed in e.g localhost:60049/unknown.html, the server will display the 404 not found page. 
 
