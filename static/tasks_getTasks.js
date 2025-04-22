fetch('/api/gettasks')
                    .then(res => res.json())
                    .then(data => {
                        const tableBody = document.querySelector('#taskTable tbody');
                        tableBody.innerHTML = ''; // Clear any existing rows

                        // Loop through the tasks_list array in the response JSON
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

                            // Append the row to the table body
                            tableBody.appendChild(row);
                        });
                    });