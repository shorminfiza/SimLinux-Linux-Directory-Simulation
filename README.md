# SimLinux-Linux-Directory-Simulation
<h1 align="center">SimLinux: Linux Directory Simulation</h1>
<p align="center"><em>A lightweight C-based simulation of a Linux directory structure.</em></p>

<hr>

<h2>📌 About the Project</h2>
<p>SimLinux is a C program that <b>simulates a basic Linux directory structure</b>, allowing users to create, navigate, and manage directories in a simplified environment. The project provides a fundamental understanding of <b>file system operations</b> and is useful for learning about hierarchical structures in computing.</p>

<h2>🚀 Features</h2>
<ul>
  <li>✅ <b>Create directories</b> – Simulate <code>mkdir</code> command.</li>
  <li>✅ <b>Navigate directories</b> – Move between directories like <code>cd</code>.</li>
  <li>✅ <b>List directory contents</b> – Mimic <code>ls</code> command behavior.</li>
  <li>✅ <b>Delete directories</b> – Remove directories just like in Linux.</li>
  <li>✅ <b>Hierarchy Representation</b> – Maintain a tree-like structure for directories.</li>
</ul>

<h2>📂 Project Structure</h2>
<pre>
SimLinux/
│── main.c            # Entry point of the simulation
│── directory.h       # Header file for directory operations
│── directory.c       # Implements directory functions
│── Makefile          # Build automation file
│── README.md         # Project documentation
</pre>

<h2>🛠 Installation & Usage</h2>

<h3>1️⃣ Clone the Repository</h3>
<pre>
git clone https://github.com/shorminfiza/SimLinux-Linux-Directory-Simulation.git
cd SimLinux-Linux-Directory-Simulation
</pre>

<h3>2️⃣ Compile the Program</h3>
<pre>
gcc main.c directory.c -o simlinux
</pre>

<h3>3️⃣ Run the Simulation</h3>
<pre>
./simlinux
</pre>

<h2>👨‍💻 How to Use</h2>
<table>
  <tr>
    <th>Command</th>
    <th>Function</th>
  </tr>
  <tr>
    <td><code>mkdir &lt;dir&gt;</code></td>
    <td>Create a new directory</td>
  </tr>
  <tr>
    <td><code>cd &lt;dir&gt;</code></td>
    <td>Move into a directory</td>
  </tr>
  <tr>
    <td><code>ls</code></td>
    <td>List contents of the current directory</td>
  </tr>
  <tr>
    <td><code>cd ..</code></td>
    <td>Move up one level</td>
  </tr>
  <tr>
    <td><code>rmdir &lt;dir&gt;</code></td>
    <td>Remove a directory</td>
  </tr>
  <tr>
    <td><code>exit</code></td>
    <td>Close the simulation</td>
  </tr>
</table>

<h2>💡 Why Use This Project?</h2>
<ul>
  <li>🔹 Ideal for <b>students & beginners</b> learning about file systems.</li>
  <li>🔹 A great <b>mini-project</b> for C programming practice.</li>
  <li>🔹 Helps understand <b>tree data structures</b> practically.</li>
</ul>

<h2>📜 License</h2>
<p>This project is licensed under the <b>MIT License</b> – feel free to modify and contribute!</p>
