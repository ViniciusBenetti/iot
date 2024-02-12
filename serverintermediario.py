# -*- coding: utf-8 -*-

from flask import Flask, request, jsonify,render_template
from flask_cors import CORS
import mysql.connector

conexao = mysql.connector.connect(
    host="secreto",
    database="secreto",
    user="secreto",
    password="secreto+",
    port=3306,
)

cursor = conexao.cursor()

app = Flask(__name__)

//CORS para comunicação de servidores
CORS(app)

//rota principal, onde receberá requisições e mandará para o arduino
@app.route('/', methods=['POST', 'GET'])
def rota_do_flask():
    global ultima_resposta_json
    
    if request.method == 'POST':
        //pegue todos os valores da requisição e retorne apenas o que não está vazio, além disso, deixe o ultimo clicado armazenado para o arduino
        parametro = request.form
        ultimavenda = parametro.get('ultima')
        dinheiroacumulado = parametro.get('acumulado')
        metadiaria = parametro.get('metadiaria')
        temperatura = parametro.get('temperatura')
        frasedodia = parametro.get('frasedodia')

        if ultimavenda is not None:
            ultima_resposta_json = {"venda": "ultima"}

        elif dinheiroacumulado is not None:
            ultima_resposta_json = {"acumulado": "dinheiro"}

        elif metadiaria is not None:
            ultima_resposta_json = {"meta": "metadiaria"}

        elif temperatura is not None:
            ultima_resposta_json = {"temp": "temperatura"}

        elif frasedodia is not None:
            ultima_resposta_json = {"frase": "frasedodia"}

        else:
            ultima_resposta_json = {"erro de conexão flask/userinput"}

        return jsonify(ultima_resposta_json)

    elif request.method == 'GET':
        //arduino vai pegar a ultima requisição
        return jsonify(ultima_resposta_json)

//endpoint da hotmart para  enviar seu webhook
@app.route("/vendas", methods=["POST"])
def vendas():
    if request.method == "POST":
      //manter conexao
        conexao = mysql.connector.connect(
        host="secreto",
        database="secreto",
        user="secreto",
        password="secreto",
        port=3306,
        )

        cursor = conexao.cursor()
        try:
            //pegando os dados da webhook
            dados = request.json
            print('Solicitação recebida:', dados)
            
            order_date = dados.get('data', {}).get('purchase', {}).get('order_date')
            price_value = dados.get('data', {}).get('purchase', {}).get('price', {}).get('value')
            try:
              cursor.execute("""
                INSERT INTO z (x,y) 
                VALUES (%s,%s)
            """, (order_date,price_value,))
            
              conexao.commit()
            except Exception as e:
              print("Erro durante a execução:",str(e))

            return jsonify({"mensagem": "Solicitação recebida com sucesso", "order_date": order_date, "price": price_value})
        except Exception as e:
            print("Erro durante a execução:",str(e))
            return jsonify({"erro": str(e)}), 500
    else:
        print("Erro durante a execução:",str(e))
        return jsonify({"erro": "Método não permitido"}), 405

      
if __name__ == "__main__":
    app.run(host=0, port=0)
