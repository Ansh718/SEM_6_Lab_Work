import random
responses = {
    "greeting": ["Hello! How can I assist you?", "Hi! How can I assist you?", "Welcome to our online store! How can I assist you?"],
    "farewell": ["Thank you for visiting our store. Have a great day!", "Goodbye! Come back soon!", "See you again!"],
    "thanks": ["You're welcome!", "No problem!", "Glad to help!"],
    "product_inquiry": ["Sure, let me check that for you.", "Certainly! I'll find the information about that product."],
    "order_status": ["Please provide your order number, and I'll check its status.", "I can help you with that. What's your order number?"],
    "shipping_status": ["To track your order, please provide your order number.", "I'll assist you with the shipping status. What's your order number?"],
    "product_category": ["We offer a wide range of product categories, including shoes, shirts, and trousers.", "Our store has products in different categories such as shoes, shirts, and trousers."],
    "shoes_range": ["Sports shoes range from 1000-15,000\nSneakers range: 1,000-40,000"],
    "trouser_range": ["Chinos: 1,200-3,000\nFormals: 1,500-4,000"],
    "shirt_range": ["Formals: 2,000-5,000\nParty Wear: 1,000-4,000"],
    "discount_offers": [
        "Enjoy up to 30% off on selected items! Hurry, grab your favorites before they're gone.",
        "Get exclusive discounts of up to 40% on your favorite brands! Shop now and save big.",
        "Limited-time offer: Buy 1 get 1 free on selected items! Don't miss out on this amazing deal."
    ],
    "loyalty_points": [
        "Earn loyalty points with every purchase! Redeem points for exciting rewards.",
        "Join our loyalty program and earn points on every order. Start earning rewards today!",
        "Become a loyal customer and unlock exclusive benefits, including redeemable loyalty points."
    ],
    "shirt_brands": ["We carry top brands like Armani, Calvin Klein, and Ralph Lauren for shirts."],
    "trouser_brands": ["Explore trousers from renowned brands such as Levi's, Dockers, and Hugo Boss."],
    "shoe_brands": ["Discover shoes from popular brands like Nike, Adidas, and Puma."],
    "default": ["I'm sorry, I didn't understand. Could you please rephrase that?", "I'm still learning. Can you provide more details?"]
}
def generate_response(user_input):
    user_input = user_input.lower()

    if "hello" in user_input or user_input=="hi":
        return random.choice(responses["greeting"])
    elif "goodbye" in user_input or "bye" in user_input:
        return random.choice(responses["farewell"])
    elif "thank" in user_input:
        return random.choice(responses["thanks"])
    elif "shipping" in user_input:
        return random.choice(responses["shipping_status"])
    elif "order" in user_input:
        return random.choice(responses["order_status"])
    elif "product" in user_input or "category" in user_input:
        return random.choice(responses["product_category"])
    elif "shoes" in user_input:
        return random.choice(responses["shoes_range"])
    elif "trouser" in user_input:
        return random.choice(responses["trouser_range"])
    elif "shirt" in user_input:
        return random.choice(responses["shirt_range"])
    elif "offer" in user_input or "discount" in user_input or "combo" in user_input:
        return random.choice(responses["discount_offers"])
    elif "loyalty" in user_input or "points" in user_input:
        return random.choice(responses["loyalty_points"])
    elif "shirt" in user_input and "brand" in user_input:
        return random.choice(responses["shirt_brands"])
    elif "trouser" in user_input and "brand" in user_input:
        return random.choice(responses["trouser_brands"])
    elif "shoe" in user_input and "brand" in user_input:
        return random.choice(responses["shoe_brands"])
    else:
        return random.choice(responses["default"])

print("Chatbot: Hi! Welcome to our online store. How can I assist you today?")
while True:
    user_input = input("You: ")
    response = generate_response(user_input)
    print("Chatbot:", response)
    if(response in ["Thank you for visiting our store. Have a great day!", "Goodbye! Come back soon!"]):
        break