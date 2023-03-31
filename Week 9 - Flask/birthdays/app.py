import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        print(request.values)
        request_type = request.form.get("request_type")
        # If post request is from submitting a birthday, write it to the database.
        if request_type == "Submit":
            name = request.form.get("name")
            date = request.form.get("date")
            db.execute("INSERT INTO birthdays (name, month, day, year) VALUES (?, ?, ?, ?)", name, date[5:7], date[8:10], date[0:4])
        # TODO: If post request is from deleting entry, delete it in database
        if request_type == "🗑️":
            id = request.form.get("id")
            db.execute("DELETE FROM birthdays WHERE id = ?", id)
        return redirect("/")

    else:

        birthdays = db.execute("SELECT * FROM birthdays")
        print(birthdays)

        return render_template("index.html", birthdays=birthdays)


