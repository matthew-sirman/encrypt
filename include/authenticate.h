//
// Created by matthew on 26/05/2020.
//

#ifndef ENCRYPT_AUTHENTICATE_H
#define ENCRYPT_AUTHENTICATE_H

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>

#include "safeRandom.h"
#include "sha.h"
#include "key.h"

// The URL location of the current active keys. A cURL request here will return JSON content holding a set
// of possible validation keys for an id token.
const std::string MICROSOFT_AUTH_KEY_URL = "https://login.microsoftonline.com/common/discovery/v2.0/keys";

// Simple struct to hold a query alongside a number used once (for verification)
struct QueryURL {
    std::string url = "";
    unsigned numberUsedOnce = 0;

    QueryURL() = default;

    QueryURL(const std::string &url, unsigned numberUsedOnce)
            : url(url), numberUsedOnce(numberUsedOnce) {}
};

enum MicrosoftAccountAuthState {
    AUTHENTICATED,
    RECEIVED_ERRONEOUS_TOKEN,
    NO_MATCHING_KEY,
    INVALID_TOKEN,
    INVALID_SIGNATURE
};

// Authenticate a Microsoft Account to check a user is who they say they are
MicrosoftAccountAuthState authenticateMicrosoftAccount(std::string idToken, const std::string &clientID, unsigned expectedNumUsedOnce,
                                  const std::string &expectedEmail);

// Returns a URL that the user must open in their web browser to authenticate themselves through a Microsoft
// account
QueryURL getMicrosoftAccountIDQueryURL(const std::string &clientID, const std::string &redirectURL);

// Open a simple HTTP listen server that will listen for a response from a certain address. It will return a success
// or error message to the user, and will return the HTTP request it received. After receiving a single request,
// the server will shut itself down and return.
std::string openOneShotHTTPAuthenticationServer(const std::string &serverAddress, unsigned short port,
                                                const std::string &responseHTML = "<html><body><h1>Success</h1></body></html>");

// Get a JSON object of the response from a URL
nlohmann::json httpGetJson(const std::string &url);

// For internal use; a cURL callback function
static size_t writeCallback(void *contents, size_t size, size_t nMem, void *userP);

std::string decodeBase64String(std::string base64);

uint2048 EMSA_PKCS1_v1_5_SHA(const std::string &message);

#endif //ENCRYPT_AUTHENTICATE_H
