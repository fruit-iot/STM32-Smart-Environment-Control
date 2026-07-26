import sqlite3
import numpy as np

from sklearn.linear_model import LinearRegression



def predict_temperature():


    conn=sqlite3.connect(
        "temperature.db"
    )


    data=conn.execute(
    """
    SELECT temp
    FROM temperature
    ORDER BY id
    """
    ).fetchall()


    conn.close()



    if len(data)<5:

        return "数据不足"



    temps=np.array(
        data
    )


    x=np.arange(
        len(temps)
    ).reshape(-1,1)


    y=temps.reshape(-1,1)



    model=LinearRegression()


    model.fit(
        x,
        y
    )


    future=len(temps)+5


    prediction=model.predict(
        [[future]]
    )


    return round(
        float(prediction[0]),
        2
    )

from sklearn.ensemble import IsolationForest



def detect():

    import sqlite3
    import pandas as pd


    conn=sqlite3.connect(
        "temperature.db"
    )


    df=pd.read_sql(
    """
    SELECT temp
    FROM temperature
    """,
    conn
    )


    if len(df)<10:

        return "数据不足"



    model=IsolationForest(
        contamination=0.1
    )


    result=model.fit_predict(
        df[['temp']]
    )



    if result[-1]==-1:

        return "⚠ 温度异常"


    else:

        return "正常"
