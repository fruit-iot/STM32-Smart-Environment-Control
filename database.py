import sqlite3
from datetime import datetime


DB="temperature.db"



def init_db():

    conn=sqlite3.connect(DB)

    c=conn.cursor()


    c.execute("""
    CREATE TABLE IF NOT EXISTS temperature(

        id INTEGER PRIMARY KEY AUTOINCREMENT,

        temp REAL,

        threshold REAL,

        speed INTEGER,

        humidity REAL,

        time TEXT

    )
    """)


    conn.commit()

    conn.close()



def save_data(temp,threshold,speed,humidity):


    conn=sqlite3.connect(DB)

    c=conn.cursor()


    c.execute(
    """
    INSERT INTO temperature
    VALUES(NULL,?,?,?,?,?)
    """,

    (
    temp,
    threshold,
    speed,
    humidity,
    datetime.now().strftime("%H:%M:%S")
    )

    )


    conn.commit()

    conn.close()



def get_history():

    conn=sqlite3.connect(DB)

    c=conn.cursor()


    result=c.execute(
    """
    SELECT *
    FROM temperature
    ORDER BY id DESC
    LIMIT 50
    """
    ).fetchall()


    conn.close()


    return result
