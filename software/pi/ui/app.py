from flask import Flask, render_template, request, flash
from wtforms import Form, TextField, TextAreaField, validators, StringField, SubmitField
import datetime
import random
import numpy as np
import matplotlib.pyplot as plt

app = Flask(__name__)
app.config.from_object(__name__)
app.config['SECRET_KEY'] = '7d441f27d441f27567d441f2b6176b'

class ReusableForm(Form):
    name = TextField('mm to mv:', validators=[validators.required()])

@app.route("/", methods=['GET', 'POST'])
def hello():
    form = ReusableForm(request.form)

    print(form.errors)
    if request.method == 'POST':
        name=request.form['name']
        print(name)

        if form.validate():
            # Save the comment here.
            flash('Hello ' + name)
        else:
            flash('All the form fields are required. ')

    return render_template('hello.html', form=form)

@app.route("/pi")
def index():
# Read Sensors Status
    ledRedSts = 0
    ledYlwSts = 1
    ledGrnSts = 0

    templateData = {
              'title' : 'GPIO output Status!',
              'ledRed'  : ledRedSts,
              'ledYlw'  : ledYlwSts,
              'ledGrn'  : ledGrnSts,
        }
    return render_template('index.html', **templateData)
@app.route("/<deviceName>/<action>")
def action(deviceName, action):
    # if deviceName == 'ledRed':
    #     actuator = ledRed
    # if deviceName == 'ledYlw':
    #     actuator = ledYlw
    # if deviceName == 'ledGrn':
    #     actuator = ledGrn

    if action == "on":
        print('on')
    if action == "off":
        print('off')

    ledRedSts = 1
    ledYlwSts = 1
    ledGrnSts = 0

    templateData = {
              'ledRed'  : ledRedSts,
              'ledYlw'  : ledYlwSts,
              'ledGrn'  : ledGrnSts,
    }
    return render_template('index.html', **templateData)

@app.route("/distance")
def getDistance():
    a = np.random.rand(10)
    plt.clf()
    plt.plot(a)
    plt.savefig('static/test.jpg')
    return str(random.random())


if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80, debug=True)
