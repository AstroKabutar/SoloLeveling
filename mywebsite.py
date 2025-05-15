from flask import Flask, render_template
import os

app = Flask(
    __name__,
    template_folder = "htmls",
    static_folder = "statics"    
)

@app.route("/Shahin")
def index():
    return render_template("index.html");

if __name__ == "__main__":
    port_no = os.environ.get("PORT");
    app.run(host='0.0.0.0', port=port_no, debug=True);
