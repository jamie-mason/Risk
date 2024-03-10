#include "Attack.h" //Includes a header file for attack class

// Function to initialize the attack phase
void Attack::attackInitalization(Player* player, Deck* deck) {
    // Notify the player about the start of the attack phase
    Phase::notify(player, "Attack", "");

    // Set player and deck attributes for this attack phase
    this->player = player;  // Store the player object
    this->deck = deck;  // Store the deck object

    // Get the list of countries owned by the player
    countries = this->player->getCountries();  // Retrieve countries owned by the player

    // Store the player ID and the number of countries owned before the attack phase
    id = this->player->getID();  // Get the player's ID
    int countriesOwnedBeforeAttackPhase = player->getCountries().size();  // Count of countries owned by player

    // Prompt the player to choose whether to initiate an attack
    char response;
    std::cout << "Do you wish to attack during this turn Player " << id
        << " (Y/y to continue)?" << std::endl;  // Prompt for attack initiation
    std::cin >> response;  // Get player response

    // If the player chooses to attack, proceed with the attack phase
    if (toupper(response) == 'Y') {
        updateAttack(); // Update the possible attack options
        attackProcedure(); // Initiate the attack procedure
    }

    // If the player conquered new countries, draw a card from the deck
    if (player->getCountries().size() > countriesOwnedBeforeAttackPhase) {
        player->getHand()->getCard(deck->Draw());  // Draw a card from the deck
    }

    // Notify the end of the attack phase
    std::cout << "End of the attack phase." << std::endl;  // Display end of attack phase message
}

// Function to update the possible attack options based on player's countries
void Attack::updateAttack() {
    std::vector<Country*> borderingCountries;  // Vector to store bordering countries
    attackBase.clear(); // Clear the list of attack bases from previous updates
    bool isAdded = false;  // Flag to track if the attack base has been added

    // Loop through the player's countries to identify possible attack bases
    for (size_t i = 0; i < countries.size(); i++) {
        isAdded = false;  // Reset the flag for each country
        borderingCountries = countries.at(i)->getBorderingCountries(); // Get the countries bordering the current country

        // Loop through the bordering countries to identify potential targets
        for (size_t j = 0; j < borderingCountries.size(); j++) {
            // Check if the bordering country belongs to an opponent
            if (id != borderingCountries.at(j)->getOwner()->getID()) {
                // Add the current country as an attack base if it hasn't been added yet
                if (!isAdded) {
                    attackBase.push_back(countries.at(i));  // Add the country as an attack base
                    isAdded = true;  // Set the flag to indicate addition
                }
                // Add the bordering country to the list of attack possibilities if not already present
                if (!isContained(borderingCountries.at(j), attackPossibilities))
                    attackPossibilities.push_back(borderingCountries.at(j));  // Add the country to attack possibilities
            }
        }
    }
}
void Attack::attackProcedure() {
    double raw, fractpart, intpart;  // Variables for parsing user input
    bool good = false;  // Flag to indicate valid input
    int numAttack = 0;  // Counter for valid attack options
    std::vector<Country*> enemyCountries;  // Vector to store enemy countries
    int input;  // Variable to store user input
    Country* base;  // Pointer to the attacking country
    Country* target;  // Pointer to the target country
    Player* att;  // Pointer to the attacking player
    Player* def;  // Pointer to the defending player
    std::vector<int> valid;  // Vector to store valid input options

    // Display the player's countries eligible for attack
    this->player->showCountries();  // Show the countries owned by the player
    std::cout << "Input Index|Country Name|Armies|Enemies Around" << std::endl;
    std::cout << std::endl;

    // Loop through the possible attack bases to display available options
    for (size_t i = 0; i < attackBase.size(); i++) {
        attackBase.at(i)->updateInfo();  // Update information about the country
        if (attackBase.at(i)->getCanAttack()) {  // Check if the country can attack
            std::cout << i + 1 << "\t|" << attackBase.at(i)->getName() << "|"
                << attackBase.at(i)->getArmies() << "|"
                << attackBase.at(i)->getNumEnemiesAround() << std::endl;  // Display country information
            valid.push_back(i + 1);  // Store the index as a valid option
            numAttack++;  // Increment the counter for valid attack options
        }
    }

    // Check if there are valid countries to attack from
    if (numAttack < 1) {
        std::cout << "No valid country to attack from" << std::endl;  // Display message if no valid options
        return;  // Exit the function
    }

    // Prompt the player to choose the attack base
    std::cout << "Select which country you would like to attack from" << std::endl;
    do {
        good = validateSpecNumericInput(input, valid);  // Validate user input
    } while (!good);
    base = attackBase.at(input - 1);  // Set the attacking country based on user input
    std::cout << "Attacking From " << base->getName() << std::endl;  // Display selected attacking country
    std::cout << "Input Index| Country Name|Armies|Owner" << std::endl;
    std::cout << std::endl;

    // Display the enemy countries that can be attacked
    enemyCountries = base->getBorderingEnemies();  // Get the bordering enemy countries
    valid.clear();  // Clear the vector of valid options
    for (size_t i = 0; i < enemyCountries.size(); i++) {
        std::cout << i + 1 << "\t| " << enemyCountries.at(i)->getName() << "| "
            << enemyCountries.at(i)->getArmies() << "|"
            << enemyCountries.at(i)->getOwner()->getID() << std::endl;  // Display information about enemy countries
        valid.push_back(i + 1);  // Store the index as a valid option
    }

    // Prompt the player to choose the target country
    std::cout << "Select which country you would like to attack" << std::endl;
    good = false;
    do {
        good = validateSpecNumericInput(input, valid);  // Validate user input
    } while (!good);
    target = enemyCountries.at(input - 1);  // Set the target country based on user input
    att = base->getOwner();  // Get the attacking player
    def = target->getOwner();  // Get the defending player

    // Execute the attack and handle the outcome
    if (userAttack(base, target)) {  // If the attack is successful
        good = false;  // Reset the flag for valid input
        def->removeCountry(target);  // Remove the target country from the defending player
        target->setOwner(att);  // Set the attacker as the owner of the target country
        att->addCountry(target);  // Add the target country to the attacker's list of countries
        std::cout << "Select how many armies to move in your new country" << std::endl;
        std::cout << "Armies available: " << base->getArmies() - 1 << std::endl;
        do {
            good = validateNumericInput(input, 1, base->getArmies() - 1);  // Validate user input for army movement
        } while (!good);
        base->removeArmies(input);  // Remove armies from the attacking country
        target->addArmies(input);  // Add armies to the target country
    }

    // Display the player's updated countries
    att->showCountries();

    // Prompt the player to continue attacking
    char response;
    std::cout << "Do you wish to attack again Player " << id << " (Y/y to continue)?"
        << std::endl;
    std::cin >> response;
    if (toupper(response) == 'Y') {
        updateAttack();  // Update possible attack options
        attackProcedure();  // Execute the attack procedure recursively
        return;
    }
}

bool Attack::userAttack(Country* base, Country* target) {
    // Get the owners of the attacking and defending countries
    Player* att = base->getOwner();  // Attacking player
    Player* def = target->getOwner();  // Defending player
    int attDice = 0;  // Number of dice for the attacker
    int defDice = 0;  // Number of dice for the defender
    int checks = 0;  // Number of comparisons between dice rolls
    std::vector<int> attResults;  // Results of the attacker's dice rolls
    std::vector<int> defResults;  // Results of the defender's dice rolls

    // Notify the players about the attack
    std::string message = "Attacking " + target->getName() + "'s " +
        std::to_string(target->getArmies()) + " armies (owned by " + def->getName() + ") with " +
        base->getName() + "'s " + std::to_string(base->getArmies()) + " armies.";
    Phase::notify(att, "Attack", message);

    // Loop until one side wins or the attacker decides to stop
    while (true) {
        // Determine the number of dice for the attacker based on the number of armies
        if (base->getArmies() > 3)
            attDice = 3;
        else if (base->getArmies() == 1)
            attDice = 1;
        else
            attDice = base->getArmies() - 1;

        // Determine the number of dice for the defender based on the number of armies
        if (target->getArmies() > 2)
            defDice = 2;
        else
            defDice = target->getArmies();

        // Prompt players to select the number of dice to roll
        std::cout << "Attack select dice (1-" << attDice << "): " << std::endl;
        bool good = false;  // Flag to indicate valid input
        int input;  // Variable to store user input
        do {
            good = validateNumericInput(input, 1, attDice);  // Validate user input
        } while (!good);
        attDice = input;  // Set the number of dice for the attacker
        good = false;  // Reset the flag for valid input
        std::cout << "Defender select dice(1-" << defDice << "): " << std::endl;
        do {
            good = validateNumericInput(input, 1, defDice);  // Validate user input
        } while (!good);
        defDice = input;  // Set the number of dice for the defender
        attResults = att->rollDie(attDice);  // Roll the attacker's dice
        defResults = def->rollDie(defDice);  // Roll the defender's dice
        // Determine the number of comparisons based on the smaller dice count
        if (attResults.size() > defResults.size())
            checks = defResults.size();
        else
            checks = attResults.size();

        // Display the results of the dice roll
        std::cout << "*****Dice Roll*****" << std::endl;
        std::cout << "Dice A/D: " << attDice << "/" << defDice << std::endl;
        std::cout << "Armies A/D: " << base->getArmies() << "/"
            << target->getArmies() << std::endl;
        for (int i = 0; i < checks; i++) {
            std::cout << "Dice Comparison " << std::endl;
            std::cout << "Attack Dice: " << attResults.at(attResults.size() - 1 - i)
                << std::endl;
            std::cout << "Defense Dice: " << defResults.at(defResults.size() - 1 - i)
                << std::endl;
            // Compare the attacker's and defender's dice rolls
            if (attResults.at(attResults.size() - 1 - i)
                <= defResults.at(defResults.size() - 1 - i)) {
                base->removeArmies(1);  // Remove an army from the attacker
                if (base->getArmies() <= 1) {  // Check if the attacker loses
                    std::cout << "Defender wins" << std::endl;
                    return false;  // Return false indicating defender's victory
                }
            }
            else {
                target->removeArmies(1);  // Remove an army from the defender
                if (target->getArmies() == 0) {  // Check if the defender loses
                    std::cout << "Attacker wins" << std::endl;
                    return true;  // Return true indicating attacker's victory
                }
            }

        }
        // Prompt the player to continue attacking
        char response;
        std::cout << "Do you wish to attack again " << target->getName()
            << " (Y/y to continue)?" << std::endl;
        std::cin >> response;
        if (toupper(response) != 'Y') {
            return false;  // Return false if the player chooses not to continue attacking
        }
    }
}


bool Attack::isContained(Country* possibility, std::vector<Country*> c) {
    // Loop through the vector of countries
    for (size_t i = 0; i < c.size(); i++) {
        // Check if the name of the possibility matches the name of a country in the vector
        if (possibility->getName() == c.at(i)->getName())
            return true;  // Return true if a match is found
    }
    return false;  // Return false if no match is found
}

// Function to validate specific numeric input
bool Attack::validateSpecNumericInput(int& input, std::vector<int> poss) {
    double raw, fractpart, intpart;
    std::cin >> raw;  // Read user input
    if (std::cin) {  // Check if input was successfully read
        fractpart = modf(raw, &intpart);  // Separate integer and fractional parts
        input = (int)intpart;  // Convert the integer part to an integer
        if (fractpart != 0) {  // Check if there is a non-zero fractional part
            std::cout << "Invalid Input! Number not integer" << std::endl;  // Notify the user
            return false;  // Return false indicating validation failure
        }
    }
    if (!std::cin) {  // Check if input was not successfully read
        std::cout << "Invalid Input! Number not numeric" << std::endl;  // Notify the user
        std::cin.clear();  // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the input
        return false;  // Return false indicating validation failure
    }
    else if (!(std::find(poss.begin(), poss.end(), input) != poss.end())) {
        // Check if the input is not in the list of possible values
        std::cout << "Invalid Input! Number not valid" << std::endl;  // Notify the user
        std::cin.clear();  // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the input
        return false;  // Return false indicating validation failure
    }
    else
        return true;  // Return true indicating validation success
}


// Function to validate numeric input within a range
bool Attack::validateNumericInput(int& input, int lower, int upper) {
    double raw, fractpart, intpart;
    std::cin >> raw;  // Read input from the user
    if (std::cin) {
        fractpart = modf(raw, &intpart);  // Extract the fractional and integer parts
        input = (int)intpart;  // Convert the raw input to an integer
        if (fractpart != 0) {
            // If the input is not an integer, display an error message
            std::cout << "Invalid Input! Number not integer" << std::endl;
            return false;  // Return false to indicate validation failure
        }
    }
    // If the input stream is not in a good state (e.g., input is not numeric)
    if (!std::cin) {
        // Display an error message and clear the input stream
        std::cout << "Invalid Input! Number not numeric" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;  // Return false to indicate validation failure
    }
    // If the input is not within the specified range
    else if (input < lower || input > upper) {
        // Display an error message and clear the input stream
        std::cout << "Invalid Input! Number out of range" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;  // Return false to indicate validation failure
    }
    else
        return true;  // Return true to indicate successful validation
}


// Function to execute an attack
void Attack::attack(Deck* currDeck, Player* player, Country* sourceCountry, Country* destinationCountry, int numDice, int numArmiesToMove) {
    // Validate the number of dice and other conditions for the attack
    if (numDice > 3 || numDice > std::min(3, sourceCountry->getArmies() - 1)) {
        // Check if the number of dice exceeds the maximum allowed or available armies
        std::cout << "Invalid amount of dice chosen." << std::endl;
        return;  // Exit the function if conditions are not met
    }

    if (player == NULL) {
        // Check if the player is set
        std::cout << "Player must be set." << std::endl;
        return;  // Exit the function if player is not set
    }

    if (sourceCountry->getOwner() != player) {
        // Check if the player owns the source country
        std::cout << "You cannot attack with a country you do not own." << std::endl;
        return;  // Exit the function if player does not own the source country
    }

    if (sourceCountry == NULL || destinationCountry == NULL) {
        // Check if both source and destination countries are set
        std::cout << "Source and destination must be set when attacking." << std::endl;
        return;  // Exit the function if either source or destination country is not set
    }

    // Notify about the attack
    std::string message = "Attacking " + destinationCountry->getName() + "'s " +
        std::to_string(destinationCountry->getArmies()) + " armies (owned by " + destinationCountry->getOwner()->getName() + ") with " +
        sourceCountry->getName() + "'s " + std::to_string(sourceCountry->getArmies()) + " armies.";
    Phase::notify(player, "Attack", message);

    bool successfulTakeover = false;
    std::vector<int> attackResults = sourceCountry->getOwner()->rollDie(numDice);
    std::vector<int> defenseResults = destinationCountry->getOwner()->rollDie(destinationCountry->getOwner()->defensiveDice(std::min(2, destinationCountry->getArmies())));

    // Resolve the attack based on dice rolls
    for (size_t i = 0; i < std::min(attackResults.size(), defenseResults.size()); i++) {
        std::cout << "Attack dice: " << attackResults[attackResults.size() - 1 - i] << std::endl;
        std::cout << "Defense dice: " << defenseResults[defenseResults.size() - 1 - i] << std::endl;
        if (attackResults[attackResults.size() - 1 - i] > defenseResults[defenseResults.size() - 1 - i]) {
            // Attacker wins the dice roll
            std::cout << "Attacker wins removing one army from " << destinationCountry->getName() << std::endl;
            destinationCountry->removeArmies(1);

            if (destinationCountry->getArmies() == 0) {
                // Destination country is conquered
                std::cout << player->getName() << " captured new country " << destinationCountry->getName() << std::endl;
                destinationCountry->getOwner()->removeCountry(destinationCountry);
                player->addCountry(destinationCountry);
                destinationCountry->setOwner(player);
                int numMoving = std::min(numArmiesToMove, sourceCountry->getArmies() - 1);
                destinationCountry->addArmies(numMoving);
                sourceCountry->removeArmies(numMoving);
                successfulTakeover = true;
            }
        }
        else {
            // Defender wins the dice roll
            std::cout << "Defender wins removing one army from " << sourceCountry->getName() << std::endl;
            sourceCountry->removeArmies(1);
        }
    }

    sourceCountry->updateInfo();
    destinationCountry->updateInfo();

    // If successful, draw a card
    if (player->getHand()->getNumberOfCards() < 5 && successfulTakeover) {
        // Check if the player has less than 5 cards and the attack was successful
        if (currDeck->getNumberCards() > 0) {
            // Draw a card from the deck if cards are available
            player->getHand()->getCard(currDeck->Draw());
        }
    }
}

// Function to notify the observer about an attack
void Attack::notifyObserver(Player* player, std::string message) {
    notify(player, "Attack", message);
}
