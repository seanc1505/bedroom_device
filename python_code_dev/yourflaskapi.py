from flask import Flask, request, jsonify

app = Flask(__name__)

VERIFY_TOKEN = "verify token"

@app.route('/webhook', methods=['GET', 'POST'])
def webhook():
    if request.method == 'GET':
        # Strava's validation challenge
        challenge = request.args.get('hub.challenge')
        verify_token = request.args.get('hub.verify_token')
        
        if verify_token == VERIFY_TOKEN:
            return jsonify({'hub.challenge': challenge})
        else:
            return 'Invalid verify token', 403

    if request.method == 'POST':
        # Handle the incoming event data
        event = request.get_json()
        # Process the event (e.g., store it in a database, trigger other actions)
        print(event)
        return '', 200

if __name__ == '__main__':
    app.run(port=5000)
