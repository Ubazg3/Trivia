# Trivia Game – C# WPF Client & C++ Server

This is a multiplayer trivia game project developed as part of a self-learning journey in computer science, networking, and UI/UX development.

The system includes:
- 🖥️ **C# WPF Client** – A modern desktop application with a graphical interface
- ⚙️ **C++ Server** *(not included here)* – Handles networking, game logic, and data flow

---

## 🧠 Technologies Used

- **Frontend:** C# (.NET WPF, XAML)
- **Networking:** TCP Sockets (custom binary protocol)
- **Serialization:** Manual + JSON-based parsing
- **Tools:** Visual Studio, .NET, Git

---

## 🎮 Features

- Full user authentication (login, signup)
- Create, join, and leave trivia rooms
- Real-time multiplayer communication
- Server interaction via TCP (with custom headers and message length parsing)
- Dynamic navigation between pages in the client
- Robust deserialization system

---

## 📁 Project Structure

client/
├── App.xaml / App.xaml.cs
├── MainWindow.xaml
├── Communicator.cs # Handles socket communication
├── Deserializer.cs # Parses incoming packets
├── Login.xaml / .cs # Login page UI + logic
├── JoinRoom.xaml / .cs # Room selection and joining
├── CreateRoom.xaml / .cs # Room creation screen
├── client.csproj # Project definition
└── ...

---

## 🧪 Communication Protocol

All client-server communication is structured as:

- 1 byte: Message code (e.g., LOGIN, SIGNUP, etc.)
- 4 bytes: Message length
- N bytes: JSON string or custom binary structure

---

## 🚧 Project Status

This client is **actively under development**, with ongoing improvements to stability, navigation, and error handling.  
The C++ server source is **not included** in this repository and will be released after internal testing.

---

## 📄 License

MIT License – feel free to use, modify, and build upon this project.

---

## 📬 Contact

Created by a 16-year-old student passionate about systems programming, networking, and user experience.  
For questions, feedback, or collaboration: feel free to open an issue or reach out directly.
