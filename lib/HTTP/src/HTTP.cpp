#include "HTTP.h"
#include "util.h"

void HTTP::setup(String ssid, String password)
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting network");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Network connected");
    this->server.begin();
}

void HTTP::listen()
{

    unsigned long currentTime = millis();
    unsigned long previousTime = 0;
    String request;

    // Listen to incoming clients
    WiFiClient client = server.accept();

    if (client)
    {
        Serial.println("Incoming HTTP request.");
        String currentLine = "";
        currentTime = millis();
        previousTime = currentTime;
        while (client.connected() && currentTime - previousTime <= HTTP_TIMEOUT_MS)
        {
            currentTime = millis();
            if (client.available())
            {
                // Read request
                char c = client.read();
                request += c;

                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        // Handle request
                        HTTPRequest httpRequest = this->parseRequest(getStringPart(request, '\r', 0));
                        Serial.println("Handling HTTP request: " + httpRequest.method + " " + httpRequest.path);
                        this->handleRequest(&client, httpRequest);

                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        request = "";
        client.stop();
        Serial.println("Finished processing HTTP request.");
    }
}

void HTTP::handleRequest(WiFiClient *client, HTTPRequest httpRequest)
{
    if (httpRequest.path.indexOf("/unlock/") != -1)
    {
        // Unlock
        this->sendHeader(client, 200, "application/json");
        String code = httpRequest.path.substring(httpRequest.path.lastIndexOf("/") + 1);
        this->lock->unlock(code);
    }
    else if (httpRequest.path.equals("/locked"))
    {
        this->sendHeader(client, 200, "application/json");
        String code = httpRequest.path.substring(httpRequest.path.lastIndexOf("/") + 1);
        client->println(lock->isLocked() ? "true" : "false");
    }
    else
    {
        // Home page
        this->sendHeader(client, 200, "text/html");
        this->home(client);
    }

    client->println();
}

void HTTP::sendHeader(WiFiClient *client, int status, String contentType)
{
    client->print("HTTP/1.1 ");
    client->print(status);
    client->println(" OK");
    client->println("Content-type:" + contentType);
    client->println("Connection: close");
    client->println();
}

void HTTP::home(WiFiClient *client)
{
    client->println("<html>");
    client->println("<head>");
    client->println("<title>NigMa - Connected hack toy</title>");
    client->println("</head>");
    client->println("<body>");
    client->println("<h1>NigMa " + this->settings->version + "</h1>");
    client->println("<p>A connected hack toy.</p>");
    if (this->lock->isLocked())
    {
        client->println("<p>Send a HTTP GET query to <b>/unlock/CODE</b> to try to unlock NigMa.</p>");
        client->println("<p>Send a HTTP GET query to <b>/locked</b> to gt the lock status.</p>");
    }
    else
    {
        client->println("<p>NigMa is unlocked! Congratulations!</p>");
    }

    client->println("</body>");
    client->println("</html>");
}

String HTTP::getAddress()
{
    return WiFi.localIP().toString();
}

HTTPRequest HTTP::parseRequest(String request)
{

    String method = getStringPart(request, ' ', 0);
    String path = getStringPart(request, ' ', 1);
    return HTTPRequest{method, path};
}