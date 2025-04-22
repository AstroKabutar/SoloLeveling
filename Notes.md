```cpp
#include "crow_all.h"
#include <vector>
#include <string>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/list")
    ([]
     {
         std::vector<std::string> items = {"Apple", "Banana", "Cherry"};  // Replace with your DB results

         std::ostringstream html;
         html << "<!DOCTYPE html><html><head><title>Item List</title>"
              << "<style>"
              << ".box { border: 1px solid #ccc; padding: 10px; width: 300px; background-color: #f9f9f9; }"
              << ".item { margin: 5px 0; }"
              << "</style></head><body>";

         html << "<div class='box'>";
         for (const auto& item : items)
         {
             html << "<div class='item'>" << crow::utility::escape(item) << "</div>";
         }
         html << "</div></body></html>";

         return crow::response(html.str());
     });

    app.port(18080).multithreaded().run();
}
```



# Crow API dynamically generated client side table
```html
<!DOCTYPE html>
<html>
<head>
    <title>Items Page</title>
    <style>
        .box { border: 1px solid #ccc; padding: 10px; width: 300px; background: #0000003d; }
    </style>
</head>
<body>
    <div class="box" id="item-box">Loading...</div>
    <div class="box" id="item-box-2" style="position: absolute; top: 120px; left: 300px; width: 120px;">Loading...</div>

    <script>
        fetch('/api/gettasks')
            .then(res => res.json())
            .then(data => {
                const box = document.getElementById('item-box');
                box.innerHTML = '';
                data.items.forEach(item => {
                    const div = document.createElement('div');
                    div.textContent = item;
                    box.appendChild(div);
                });
            });
    </script>

    <script>
        fetch('/api/gettasks')
            .then(res => res.json())
            .then(data => {
                const box = document.getElementById('item-box-2');
                box.innerHTML = '';
                data.items.forEach(item => {
                    const div = document.createElement('div');
                    div.textContent = item;
                    box.appendChild(div);
                });
            });
</script>
</body>
</html>
```
```cpp
    CROW_ROUTE(app, "/api/gettasks")
    ([] {
        crow::json::wvalue json;
        std::vector<std::string> items = {"Apple", "Banana", "Cherry"};
        json["items"] = items;
        return crow::response(json);
    });
```