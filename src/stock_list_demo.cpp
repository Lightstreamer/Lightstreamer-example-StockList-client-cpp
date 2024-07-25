#include "Lightstreamer/LightstreamerClient.h"
#include "Lightstreamer/SubscriptionListener.h"
#include "Lightstreamer/ConsoleLoggerProvider.h"
#include <iostream>
#include <iomanip>

using namespace Lightstreamer;

class MySubscriptionListener: public SubscriptionListener {
public:
  void onItemUpdate(ItemUpdate& update) override {
    std::cout 
      << std::setw(19) << std::left << update.getValue("stock_name")
      << ": Last " << std::setw(6) << update.getValue("last_price")
      << " - Time " << std::setw(8) << update.getValue("time")
      << " - Bid " << std::setw(5) << update.getValue("bid")
      << " - Ask " << std::setw(5) << update.getValue("ask")
      << std::endl;
  }
};

void wait_for_input() {
  std::string s;
  std::cin >> s;
}

int main() {
  LightstreamerClient::initialize([](const char* info) {
    std::cout << "Uncaught exception: " << info << std::endl;
    std::exit(1);
  });

  LightstreamerClient::setLoggerProvider(new ConsoleLoggerProvider(ConsoleLogLevel::Warn));

  // Establishing a new connection to Lightstreamer Server
  LightstreamerClient client("https://push.lightstreamer.com", "DEMO");
  client.connect();

  // Making a new Subscription in MERGE mode
  Subscription* sub = new Subscription(
    "MERGE", 
    { 
      "item1", "item2", "item3", "item4",
      "item5", "item6", "item7", "item8",
      "item9", "item10", "item11", "item12"
    }, 
    {
      "stock_name", "last_price", "time", "bid", "ask"
    }
  );
  sub->setDataAdapter("QUOTE_ADAPTER");

  // Adding the subscription listener to get notifications about new updates
  sub->addListener(new MySubscriptionListener());

  // Registering the Subscription
  client.subscribe(sub);

  // To exit, press Ctrl-D on *nix and Ctrl-Z on Windows
  wait_for_input();

  // Unsubscribing from Lightstreamer by using the subscription as key
  client.unsubscribe(sub);

  // Disconnecting
  client.disconnect();
}