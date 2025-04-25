const params = new URLSearchParams(window.location.search);
if (params.get("init") === "1") 
{
    loadTasks();
    loadPlayerStats();
}

function loadTasks() {
    fetch('/api/gettasks')
        .then(res => res.json())
        .then(data => 
            {
            const tableBody = document.querySelector('#taskTable tbody');
            tableBody.innerHTML = ''; // Clear any existing rows

            data.tasks_list.forEach(item => {
                const row = document.createElement('tr');

                const idCell = document.createElement('td');
                idCell.textContent = item.ID;
                row.appendChild(idCell);

                const taskCell = document.createElement('td');
                taskCell.textContent = item.Tasks;
                row.appendChild(taskCell);

                const importanceCell = document.createElement('td');
                importanceCell.textContent = item.Importance;
                row.appendChild(importanceCell);

                const statusCell = document.createElement('td');
                statusCell.textContent = item.Status;
                row.appendChild(statusCell);

                tableBody.appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error loading tasks:', error);
        });
}
     
function loadPlayerStats()
{
    fetch('/api/playerstats')
        .then(res => res.json())
        .then(data => 
            {
            const stats = data.Player_Stats[0];
            // Inject into the DOM
            document.getElementById('Player_Stats').innerText = `${stats.pname}\n
            ${stats.current_xp} XP\n
            Level ${stats.current_level}\n
            ${stats.required_xp} XP required\n`;
        });
}

document.getElementById("submitButton").addEventListener("click", function() {
    // Get values from the input and dropdown
    var task = document.getElementById("taskInput").value;
    var importance = document.getElementById("importanceSelect").value;

    // Check if the task is empty
    if (!task) {
        alert("Please enter a task!");
        return;
    }

    // Create the data to send in the POST request
    var data = {
        task: task,
        importance: importance
    };

    // Make the POST request using Fetch API
    fetch('http://localhost:18080/submit_task', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    })
    .then(response => response.json())
    .then(data => {
        // Handle the response here
        document.getElementById("feedback").textContent = data.message;
    })
    .catch(error => {
        // Handle any errors
        console.error('Error:', error);
        document.getElementById("feedback").textContent = "Error submitting task!";
    });
});
