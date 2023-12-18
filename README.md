
# The-luckiest-among-us

The application represents a straightforward implementation of multiplayer gaming using socket programming in C. The server-client architecture leverages sockets for communication, allowing the server to coordinate the game, distribute lucky numbers, and receive player scores. The game progresses in rounds until a player achieves a score of 20 or higher. The server, responsible for managing game logic and facilitating client interactions, logs relevant information to an output file. Clients, in turn, connect to the server, generate lucky numbers, and exchange score information. 
## Run Locally

### Server Instructions:

1. **Open a Terminal:**
   - Open a terminal or command prompt.

2. **Navigate to the Directory with Server Code:**
   - Use the `cd` command to navigate to the directory where you saved your server C file. For example:
     ```bash
     cd /path/to/your/code
     ```

3. **Compile the Server Code:**
   - Compile the server C code using a C compiler (e.g., `gcc`). Execute the following command:
     ```bash
     gcc -o srv server.c
     ```

4. **Run the Server:**
   - Run the compiled server executable using the following command:
     ```bash
     ./srv
     ```
     This will start the game server, listening on IP address `127.0.0.1` and port `55555`.

### Client Instructions:

1. **Open a New Terminal for Each Client:**
   - Open a new terminal or command prompt for each client you want to run.

2. **Navigate to the Directory with Client Code:**
   - Use the `cd` command to navigate to the directory where you saved your client C file. For example:
     ```bash
     cd /path/to/your/code
     ```

3. **Compile the Client Code:**
   - Compile the client C code using a C compiler (e.g., `gcc`). Execute the following command:
     ```bash
     gcc -o client client.c
     ```

4. **Run the Client:**
   - Run the compiled client executable using the following command:
     ```bash
     ./client 127.0.0.1 55555
     ```
     Replace `127.0.0.1` and `55555` with the actual IP address and port number of your server.

5. **Repeat for Additional Clients:**
   - If you want to run multiple clients, open additional terminals and repeat steps 1-4 for each client.

