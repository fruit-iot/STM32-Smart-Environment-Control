from flask import Flask,render_template,jsonify

from database import *

from ai_analysis import *


app=Flask(__name__)


init_db()



@app.route("/")
def index():

    data=get_history()


    return render_template(
        "index.html",
        data=data[0] if data else None
    )



@app.route("/history")
def history():

    data=get_history()


    return render_template(
        "history.html",
        data=data
    )



@app.route("/ai")
def ai():


    return render_template(

        "ai.html",

        prediction=
        predict_temperature(),

        status=
        detect()

    )



if __name__=="__main__":


    app.run(

        host="0.0.0.0",

        port=5000

    )