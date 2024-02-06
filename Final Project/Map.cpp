#include "Map.h"

Map::Map() {
    name = "";
    setContinents();
}

Map::Map(std::string name) {
    this->name = name;
    setContinents();
}
void Map::setContinents() {
    Continent asia("Asia", 7);
    asia.addCountry(new Country("Afghanistan"));
    asia.addCountry(new Country("Armenia"));
    asia.addCountry(new Country("Azerbaijan"));
    asia.addCountry(new Country("Bahrain"));
    asia.addCountry(new Country("Bangladesh"));
    asia.addCountry(new Country("Bhutan"));
    asia.addCountry(new Country("Brunei"));
    asia.addCountry(new Country("Cambodia"));
    asia.addCountry(new Country("China"));
    asia.addCountry(new Country("Cyprus"));
    asia.addCountry(new Country("Georgia"));
    asia.addCountry(new Country("India"));
    asia.addCountry(new Country("Indonesia"));
    asia.addCountry(new Country("Iran"));
    asia.addCountry(new Country("Iraq"));
    asia.addCountry(new Country("Israel"));
    asia.addCountry(new Country("Japan"));
    asia.addCountry(new Country("Jordan"));
    asia.addCountry(new Country("Kazakhstan"));
    asia.addCountry(new Country("Kuwait"));
    asia.addCountry(new Country("Kyrgyzstan"));
    asia.addCountry(new Country("Laos"));
    asia.addCountry(new Country("Lebanon"));
    asia.addCountry(new Country("Malaysia"));
    asia.addCountry(new Country("Maldives"));
    asia.addCountry(new Country("Mongolia"));
    asia.addCountry(new Country("Myanmar (Burma)"));
    asia.addCountry(new Country("Nepal"));
    asia.addCountry(new Country("North Korea"));
    asia.addCountry(new Country("Oman"));
    asia.addCountry(new Country("Pakistan"));
    asia.addCountry(new Country("Philippines"));
    asia.addCountry(new Country("Qatar"));
    asia.addCountry(new Country("Russia"));
    asia.addCountry(new Country("Saudi Arabia"));
    asia.addCountry(new Country("Singapore"));
    asia.addCountry(new Country("South Korea"));
    asia.addCountry(new Country("Sri Lanka"));
    asia.addCountry(new Country("Syria"));
    asia.addCountry(new Country("Taiwan"));
    asia.addCountry(new Country("Tajikistan"));
    asia.addCountry(new Country("Thailand"));
    asia.addCountry(new Country("Timor-Leste (East Timor)"));
    asia.addCountry(new Country("Turkey"));
    asia.addCountry(new Country("Turkmenistan"));
    asia.addCountry(new Country("United Arab Emirates"));
    asia.addCountry(new Country("Uzbekistan"));
    asia.addCountry(new Country("Vietnam"));
    asia.addCountry(new Country("Yemen"));


    

    Continent northAmerica("North America", 5);
    northAmerica.addCountry(new Country("Canada"));
    northAmerica.addCountry(new Country("USA"));
    northAmerica.addCountry(new Country("Mexico"));
    northAmerica.addCountry(new Country("Greenland"));
    northAmerica.addCountry(new Country("Antigua and Barbuda"));
    northAmerica.addCountry(new Country("Bahamas"));
    northAmerica.addCountry(new Country("Barbados"));
    northAmerica.addCountry(new Country("Belize"));
    northAmerica.addCountry(new Country("Bermuda"));
    northAmerica.addCountry(new Country("Costa Rica"));
    northAmerica.addCountry(new Country("Cuba"));
    northAmerica.addCountry(new Country("Dominica"));
    northAmerica.addCountry(new Country("Dominican Republic"));
    northAmerica.addCountry(new Country("El Salvador"));
    northAmerica.addCountry(new Country("Grenada"));
    northAmerica.addCountry(new Country("Guatemala"));
    northAmerica.addCountry(new Country("Haiti"));
    northAmerica.addCountry(new Country("Honduras"));
    northAmerica.addCountry(new Country("Jamaica"));
    northAmerica.addCountry(new Country("Nicaragua"));
    northAmerica.addCountry(new Country("Panama"));
    northAmerica.addCountry(new Country("St. Kitts and Nevis"));
    northAmerica.addCountry(new Country("St. Vincent and The Grenadines"));
    northAmerica.addCountry(new Country("Trinidad and Tobago"));
    



    Continent europe("Europe", 5);
    europe.addCountry(new Country("Albania"));
    europe.addCountry(new Country("Andorra"));
    europe.addCountry(new Country("Austria"));
    europe.addCountry(new Country("Belarus"));
    europe.addCountry(new Country("Belgium"));
    europe.addCountry(new Country("Bosnia and Herzegovina"));
    europe.addCountry(new Country("Bulgaria"));
    europe.addCountry(new Country("Croatia"));
    europe.addCountry(new Country("Cyprus"));
    europe.addCountry(new Country("Czech Republic"));
    europe.addCountry(new Country("Denmark"));
    europe.addCountry(new Country("Estonia"));
    europe.addCountry(new Country("Finland"));
    europe.addCountry(new Country("France"));
    europe.addCountry(new Country("Germany"));
    europe.addCountry(new Country("Greece"));
    europe.addCountry(new Country("Hungary"));
    europe.addCountry(new Country("Iceland"));
    europe.addCountry(new Country("Ireland"));
    europe.addCountry(new Country("Italy"));
    europe.addCountry(new Country("Kosovo"));
    europe.addCountry(new Country("Latvia"));
    europe.addCountry(new Country("Liechtenstein"));
    europe.addCountry(new Country("Lithuania"));
    europe.addCountry(new Country("Luxembourg"));
    europe.addCountry(new Country("Malta"));
    europe.addCountry(new Country("Moldova"));
    europe.addCountry(new Country("Monaco"));
    europe.addCountry(new Country("Montenegro"));
    europe.addCountry(new Country("Netherlands"));
    europe.addCountry(new Country("North Macedonia"));
    europe.addCountry(new Country("Norway"));
    europe.addCountry(new Country("Poland"));
    europe.addCountry(new Country("Portugal"));
    europe.addCountry(new Country("Romania"));
    europe.addCountry(new Country("Russia"));
    europe.addCountry(new Country("San Marino"));
    europe.addCountry(new Country("Serbia"));
    europe.addCountry(new Country("Slovakia"));
    europe.addCountry(new Country("Slovenia"));
    europe.addCountry(new Country("Spain"));
    europe.addCountry(new Country("Sweden"));
    europe.addCountry(new Country("Switzerland"));
    europe.addCountry(new Country("Turkey"));
    europe.addCountry(new Country("Ukraine"));
    europe.addCountry(new Country("United Kingdom"));
    europe.addCountry(new Country("Vatican City"));
    

    Continent southAmerica ("South America", 2);

    southAmerica.addCountry(new Country("Argentina"));
    southAmerica.addCountry(new Country("Bolivia"));
    southAmerica.addCountry(new Country("Brazil"));
    southAmerica.addCountry(new Country("Chile"));
    southAmerica.addCountry(new Country("Colombia"));
    southAmerica.addCountry(new Country("Ecuador"));
    southAmerica.addCountry(new Country("Guyana"));
    southAmerica.addCountry(new Country("Paraguay"));
    southAmerica.addCountry(new Country("Peru"));
    southAmerica.addCountry(new Country("Suriname"));
    southAmerica.addCountry(new Country("Uruguay"));
    southAmerica.addCountry(new Country("Venezuela"));
    
    Continent africa ("Africa", 3);
    africa.addCountry(new Country("Algeria"));
    africa.addCountry(new Country("Angola"));
    africa.addCountry(new Country("Benin"));
    africa.addCountry(new Country("Botswana"));
    africa.addCountry(new Country("Burkina Faso"));
    africa.addCountry(new Country("Burundi"));
    africa.addCountry(new Country("Cabo Verde"));
    africa.addCountry(new Country("Cameroon"));
    africa.addCountry(new Country("Central African Republic"));
    africa.addCountry(new Country("Chad"));
    africa.addCountry(new Country("Comoros"));
    africa.addCountry(new Country("Democratic Republic of the Congo"));
    africa.addCountry(new Country("Djibouti"));
    africa.addCountry(new Country("Egypt"));
    africa.addCountry(new Country("Equatorial Guinea"));
    africa.addCountry(new Country("Eritrea"));
    africa.addCountry(new Country("Eswatini"));
    africa.addCountry(new Country("Ethiopia"));
    africa.addCountry(new Country("Gabon"));
    africa.addCountry(new Country("Gambia"));
    africa.addCountry(new Country("Ghana"));
    africa.addCountry(new Country("Guinea"));
    africa.addCountry(new Country("Guinea-Bissau"));
    africa.addCountry(new Country("Ivory Coast"));
    africa.addCountry(new Country("Kenya"));
    africa.addCountry(new Country("Lesotho"));
    africa.addCountry(new Country("Liberia"));
    africa.addCountry(new Country("Libya"));
    africa.addCountry(new Country("Madagascar"));
    africa.addCountry(new Country("Malawi"));
    africa.addCountry(new Country("Mali"));
    africa.addCountry(new Country("Mauritania"));
    africa.addCountry(new Country("Mauritius"));
    africa.addCountry(new Country("Morocco"));
    africa.addCountry(new Country("Mozambique"));
    africa.addCountry(new Country("Namibia"));
    africa.addCountry(new Country("Niger"));
    africa.addCountry(new Country("Nigeria"));
    africa.addCountry(new Country("Republic of the Congo"));
    africa.addCountry(new Country("Rwanda"));
    africa.addCountry(new Country("São Tomé and Príncipe"));
    africa.addCountry(new Country("Senegal"));
    africa.addCountry(new Country("Seychelles"));
    africa.addCountry(new Country("Sierra Leone"));
    africa.addCountry(new Country("Somalia"));
    africa.addCountry(new Country("South Africa"));
    africa.addCountry(new Country("South Sudan"));
    africa.addCountry(new Country("Sudan"));
    africa.addCountry(new Country("Tanzania"));
    africa.addCountry(new Country("Togo"));
    africa.addCountry(new Country("Tunisia"));
    africa.addCountry(new Country("Uganda"));
    africa.addCountry(new Country("Zambia"));
    africa.addCountry(new Country("Zimbabwe"));
    
    
    Continent australasia ("Australasia", 2);
    australasia.addCountry(new Country("Australia"));
    australasia.addCountry(new Country("New Zealand"));
    australasia.addCountry(new Country("Papua New Guinea"));
    australasia.addCountry(new Country("Fiji"));
    australasia.addCountry(new Country("Solomon Islands"));
    australasia.addCountry(new Country("Vanuatu"));
    australasia.addCountry(new Country("New Caledonia"));
    australasia.addCountry(new Country("French Polynesia"));
    australasia.addCountry(new Country("Samoa"));
    australasia.addCountry(new Country("Tonga"));
    australasia.addCountry(new Country("Micronesia"));
    australasia.addCountry(new Country("Marshall Islands"));
    australasia.addCountry(new Country("Palau"));
    australasia.addCountry(new Country("Tuvalu"));
    australasia.addCountry(new Country("Kiribati"));
    australasia.addCountry(new Country("Nauru"));
    australasia.addCountry(new Country("Cook Islands"));
    australasia.addCountry(new Country("Niue"));
    australasia.addCountry(new Country("American Samoa"));
    australasia.addCountry(new Country("Norfolk Island"));
    australasia.addCountry(new Country("Wallis and Futuna"));
    australasia.addCountry(new Country("Pitcairn Islands"));
    australasia.addCountry(new Country("Tokelau"));
    australasia.addCountry(new Country("Christmas Island"));
    australasia.addCountry(new Country("Cocos (Keeling) Islands"));
    australasia.addCountry(new Country("Heard Island and McDonald Islands"));

    Continent antarctica("Antarctica", 1); 

    continents.push_back(asia);
    continents.push_back(europe);
    continents.push_back(africa);
    continents.push_back(australasia);
    continents.push_back(northAmerica);
    continents.push_back(southAmerica);
    continents.push_back(antarctica);
}
std::string Map::getName() const {
    return name;
}

std::vector<Continent>& Map::getContinents() {
    return continents;
}

std::vector<Country*>& Map::getCountries() {
    return countries;
}
void Map::connectCountries(Country* country1, Country* country2) {

}
