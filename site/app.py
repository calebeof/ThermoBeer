import json

from flask import Flask, render_template, redirect, request
from flask_socketio import SocketIO, send, emit
from flask_cors import CORS

app = Flask(__name__)
socketio = SocketIO(app)
CORS(app)

estado = {
    "RELE": 0,
    "STATUS": 0,
    "SENSOR" : 0
}

dados={
 "NOMECERVEJA":"",
 "LEVEDURA": "",
 "TIPOCERVEJA":"",
 "HIGHTEMP": 0,
 "LOWTEMP":0
}
    
    
@socketio.on('rele_acender')
def rele_acender():
 global estado
 estado["RELE"] = 1

@socketio.on('rele_apagar')
def rele_apagar():
 global estado
 estado["RELE"] = 0

@app.route("/")
def rota_inicial():
    return render_template("index.html")

@app.route("/upload", methods=["POST"])
def rota_data():
 global estado
 estado = request.get_json()
 socketio.emit("atualiza",estado)
 return "200"
 


@app.route("/download", methods=["GET"])
def rota_download():
 global estado
 return json.dumps(estado)
 
@app.route("/envio_levedura", methods=["POST"])
def rota_envio():
 global dados
 dados = request.get_json()
 socketio.emit("levedura",dados)
 return "200"
 
 
if __name__ == "__main__":
    app.run("0.0.0.0",port=8080)
