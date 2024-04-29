  <h1>Minishell</h1>

  <h2>Description</h2>
  <p>Minishell is a simple shell program developed as part of a project. It functions as a basic command-line interpreter, providing users with a prompt to enter commands and execute them.</p>

  <h2>Features</h2>
  <ul>
    <li><strong>Prompt:</strong> Minishell displays a prompt, awaiting user input for commands.</li>
    <li><strong>Command Execution:</strong> It searches and launches the appropriate executable based on the PATH environment variable, or on a relative or absolute path.</li>
    <li><strong>History:</strong> Minishell possesses functional command history functionality.</li>
    <li><strong>Redirections:</strong> Supports input (<code>&lt;</code>), output (<code>&gt;</code> and <code>&gt;&gt;</code>), and heredoc (<code>&lt;&lt;</code>) redirections.</li>
    <li><strong>Pipes:</strong> Implements pipes (<code>|</code>) to connect the output of one command to the input of another.</li>
    <li><strong>Environment Variables:</strong> Handles environment variables (e.g., <code>$PATH</code>) and substitutes them with their content.</li>
    <li><strong>Built-in Commands:</strong> Supports various built-in commands including <code>echo</code>, <code>cd</code>, <code>pwd</code>, <code>export</code>, <code>unset</code>, <code>env</code>, and <code>exit</code>.</li>
    <li><strong>Signal Handling:</strong> Manages signals such as <code>ctrl-C</code>, <code>ctrl-D</code>, and <code>ctrl-\</code> as in bash.</li>
  </ul>

  <h2>Usage</h2>
  <p>To use Minishell:</p>
  <ol>
    <li>Clone or download this repository.</li>
    <li>Compile the source files using the provided Makefile.</li>
    <li>Run the executable file to start the Minishell.</li>
    <li>Enter commands at the prompt and press Enter to execute them.</li>
  </ol>
