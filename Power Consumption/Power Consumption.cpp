/***********************************************************************
Matr.-Nr:                     3173771
Nachname/Surname:             Aly
Vorname/Given name:           Mohamed
Uni-Email:                    Mohamed.aly@stud.uni-due.de
Studiengang/Course of studies: Computer Engineering ISE
***********************************************************************/

//Task 6 //


#include <iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include <vector>
#include <tuple>

using namespace std;
fstream Houses;

int P = 200;
int A = 9;
int D = 200;
int W = 550;
int global_column = 35;


enum Usage { once, daily, mo_fr, sa_su, weekly };

//pre declaration//
class Household;
class Consumer;
class Address;
class House;
class Immobile;
class Mobile;

float AnnualcostperConsumer(Consumer* c1, Household* h);
void add_consumer_to_household(Consumer* c1);


float TotalCost(Household* h);
float TotalPower(Household* h);

Usage convertStringToEnum(string use);
string convertEnumToString(Usage use);
Usage inputUsage(char use);
//end of pre declaration//

class Device {
private:
	string description;

	Device* pnext;

public:
	Device() {
		this->pnext = nullptr;

	}

	virtual ~Device() {
		cout << "Device: " << description << " at address " << this << " has been deleted\n";

	}

	//Getting//
	string getdescription() {
		return description;
	}
	Device* getPnext() {
		return pnext;
	}


	//Setting//
	void setdescription(string value) {
		description = value;
	}
	void setPnext(Device* nextDevice) {
		pnext = nextDevice;
	}

	virtual void input() {
		cin.ignore();
		cout << "What is the description of the power consumer?\n";
		getline(cin, description);
	}


	virtual void print(int number, float priceForKw) = 0;

	virtual float annual_kWh() = 0;

	virtual Device* get_a_copy() = 0;

	virtual string get_string_for_file(char seprator) = 0;



};

class Consumer : public Device {

private:
	float watt;
	Usage use;
	static int consumerCount;
public:

	Consumer() : Device() {
		consumerCount++;
	}

	virtual ~Consumer() {
		cout << "Consumer: " << getdescription() << " at address " << this << " has been deleted\n";
		consumerCount--;
	}

	//getters&setters//

	static int getConsumerCount() {
		return consumerCount;
	}

	float getwatt() {
		return watt;
	}
	Usage getuse() {
		return use;
	}

	void setwatt(float value) {
		watt = value;
	}
	void setuse(Usage value) {
		use = value;
	}

	virtual void input() override {
		Device::input();
		cout << "how many watt it will have?\n";
		cin >> watt;
		cout << "how often it will be used?\n"
			"daily(d)\n"
			"mo_fr(m)\n"
			"once(o)\n"
			"sa_su(s)\n"
			"weekly(w) ?\n";
		char use;
		cin >> use;
		this->setuse(inputUsage(use));
	}



};

class Immobile : public Consumer {

private:
	float watt_standby;
	float operating_hours;
	float standby_hours;

public:
	Immobile() : Consumer() {

	}
	virtual ~Immobile()
	{
		cout << "Immobile: " << getdescription() << " at address " << this << " has been deleted\n";
	}



	//getters&setters//
	float getwatt_standby() {
		return watt_standby;
	}
	float getoperating_hours() {
		return operating_hours;
	}
	float getstandby_hours() {
		return standby_hours;
	}

	void setwatt_standby(float value) {
		watt_standby = value;
	}
	void setoperating_hours(float value) {
		operating_hours = value;
	}
	void setstandby_hours(float value) {
		standby_hours = value;
	}

	virtual void input() {
		Consumer::input();
		cout << "What is the wattage of the power consumer in standby mode?\n";
		cin >> watt_standby;
		cout << "What is the operating hours of the power consumer?\n";
		cin >> operating_hours;

	}


	virtual Device* get_a_copy() {
		Immobile* copy = new Immobile();
		*copy = *this;
		return copy;
	}

	virtual string get_string_for_file(char seprator) {
		string immobile = "Immobile";
		return immobile + seprator + getdescription() + seprator + to_string(getoperating_hours()) + seprator + convertEnumToString(getuse()) + seprator + to_string(getwatt()) + seprator + to_string(getwatt_standby()) + seprator;
	}

	float Annual_hours_of_use() {
		float usage_hours;
		switch (getuse()) {
		case daily:
			usage_hours = operating_hours * 365;
			break;
		case weekly:
			usage_hours = operating_hours * 52;
			break;
		case sa_su:
			usage_hours = operating_hours * 104;
			break;
		case mo_fr:
			usage_hours = operating_hours * 260;
			break;
		default:
			usage_hours = operating_hours;
			break;

		}
		return usage_hours;
	}

	float Annual_hours_of_standby() {
		float standby_hours;
		standby_hours = 8760 - Annual_hours_of_use();
		return standby_hours;


	}

	virtual float annual_kWh() {
		float total_consumption;
		total_consumption = (Annual_hours_of_use() * getwatt()) + (Annual_hours_of_standby() * watt_standby);
		return total_consumption / 1000;
	}

	virtual void print(int id, float priceForKw) {

		cout << setw(global_column) << id << ":" << getdescription() << "(At Address: " << this << " )" << endl;
		cout << setw(global_column) << "power consumption: " << this->getwatt() << " w" << endl;
		cout << setw(global_column) << "power consumption standby: " << watt_standby << " w" << endl;
		cout << setw(global_column) << "annual hours of use: " << Annual_hours_of_use() << " h" << endl;
		cout << setw(global_column) << "annual hours of standby: " << Annual_hours_of_standby() << " h" << endl;
		cout << setw(global_column) << "annual consumption: " << annual_kWh() << " kw/h" << endl;
		cout << setw(global_column) << "Annual costs: " << annual_kWh() * priceForKw << "EUR\n";


	}




};



class Mobile : public Consumer {
private:
	float Km;

public:

	Mobile() : Consumer() {
		this->Km = 0;
	}
	virtual ~Mobile()
	{
		cout << "Mobile: " << getdescription() << " at address " << this << " has been deleted\n";
	}

	//getters&setters//
	float getKm() {
		return Km;
	}

	void setKm(float value) {
		Km = value;
	}

	virtual void input() {
		Consumer::input();
		cout << "how many km will be driven?\n";
		cin >> Km;
	}


	float Annual_Km_of_use() {
		float KmUsage;
		switch (getuse()) {
		case daily:
			KmUsage = Km * 365;
			break;
		case weekly:
			KmUsage = Km * 52;
			break;
		case sa_su:
			KmUsage = Km * 104;
			break;
		case mo_fr:
			KmUsage = Km * 260;
			break;
		default:
			KmUsage = Km;
			break;

		}
		return KmUsage;
	}


	virtual float annual_kWh() override {
		float total_consumption;
		return total_consumption = (Annual_Km_of_use() * getwatt()) / 100000;
	}



	virtual Device* get_a_copy() override {
		Mobile* copy = new Mobile();
		*copy = *this;
		return copy;
	}

	virtual string get_string_for_file(char seprator) override {
		string mobile = "Mobile";
		return mobile + seprator + getdescription() + seprator + to_string(getKm()) + seprator + convertEnumToString(getuse()) + seprator + to_string(getwatt()) + seprator;
	}



	virtual void print(int number, float priceForKw) {
		cout << setw(global_column) << number << ":" << getdescription() << "(At Address: " << this << " )" << endl;
		cout << setw(global_column) << "power consumption per 100km: " << this->getwatt() / 1000 << " KW" << endl;
		cout << setw(global_column) << "Km driven : " << this->Km << "" << convertEnumToString(getuse()) << endl;
		cout << setw(global_column) << "annual consumption: " << annual_kWh() << " Kwh" << endl;
		cout << setw(global_column) << "Annual costs: " << annual_kWh() * priceForKw << " EUR" << endl;

	}


};



class Producer : public Device {
public:

	Producer() {}

	Producer(Device* device) {
		device->setPnext(nullptr);
	}
	virtual ~Producer()
	{
		cout << "Producer: " << getdescription() << " at address " << this << " has been deleted\n";
	}

	virtual void input() {
		Device::input();
	}
};

class Solar : public Producer {
private:
	float watt_peak;
	int year_of_installation;

public:
	Solar() {}

	Solar(Device* device) {
		device->setPnext(nullptr);
	}


	virtual ~Solar()
	{
		cout << "Solar: " << getdescription() << " at address " << this << " has been deleted\n";
	}

	//getters&setters//

	float getwatt_peak() {
		return watt_peak;
	}
	int getyear_of_installation() {
		return year_of_installation;
	}

	void setwatt_peak(float value) {
		watt_peak = value;
	}

	void setyear_of_installation(int value) {
		year_of_installation = value;
	}

	virtual void input() {
		Producer::input();
		cout << "What is the watt peak of the power producer?\n";
		cin >> watt_peak;
		cout << "What is the year of installation of the power producer?\n";
		cin >> year_of_installation;
	}

	virtual float annual_kWh() override {
		int current_year = 2024;
		float total_generated = getwatt_peak();
		int years_since_installation = current_year - getyear_of_installation();
		float reduction_factor = 1.0f - (0.005f * years_since_installation);
		total_generated *= reduction_factor;
		float total_kWh = total_generated;
		return -total_kWh;
	}




	virtual void print(int number, float priceForKw) {

		cout << setw(global_column) << number << ":" << getdescription() << "(At Address: " << this << " )" << endl;
		cout << setw(global_column) << "solar cells installed power: " << watt_peak << " Watt peak" << endl;
		cout << setw(global_column) << "age of solar cells : " << 2024 - year_of_installation << endl;
		cout << setw(global_column) << "annual production: " << annual_kWh() << " Kwh" << endl;
		cout << setw(global_column) << "annual savings: " << annual_kWh() * priceForKw << " EUR" << endl;

	}

	virtual Device* get_a_copy() {
		Solar* copy = new Solar(this);
		*copy = *this;
		return copy;
	}

	virtual string get_string_for_file(char seprator) {
		string solar = "Solar";
		return solar + seprator + getdescription() + seprator + to_string(getyear_of_installation()) + seprator + to_string(getwatt_peak()) + seprator;

	}




};



class Household {
private:
	int numofpersons;
	int squaremeters;
	bool waterheated;
	Device* devices;
	float powerPrice;
	string powerSupplier;
public:
	Household() : devices(nullptr) {}
	~Household() {
		Device* temp = devices;
		while (temp != nullptr) {
			Device* next = temp->getPnext();
			delete temp;
			temp = next;
		}
		cout << "Household at address: " << this << " has been deleted\n";
	}


	//Getting//

	int getNumofpersons() {
		return numofpersons;
	}
	int getSquaremeters() {
		return squaremeters;
	}
	bool getWaterheated() {
		return waterheated;
	}
	Device* getDevices() {
		return devices;
	}
	float getPowerprice() {
		return powerPrice;
	}
	string getPowersupplier() {
		return powerSupplier;
	}

	//Setting//

	void setNumofpersons(int value) {
		numofpersons = value;
	}
	void setSquaremeters(int value) {
		squaremeters = value;
	}
	void setWaterheated(bool value) {
		waterheated = value;
	}
	void setPowerprice(float value) {
		powerPrice = value;
	}
	void setPowersupplier(string value) {
		powerSupplier = value;
	}
	void setDevices(Device* devices) {

		this->devices = devices;

	}


	void  add_device_to_household(Device* d1) {
		if (this->devices == nullptr) {
			this->devices = d1;
			return;
		}
		Device* temp = this->devices;
		Device* head = temp;
		while (temp->getPnext() != nullptr) {
			temp = temp->getPnext();
		}
		temp->setPnext(d1);
		this->devices = head;
	}
	Device* MoveUp(int k) {
		int i = 1;
		Device* current = nullptr;
		Device* previous = nullptr;
		Device* beforeprevious = nullptr;




		Device* temp = this->devices;
		while (i <= k) {

			if (i == k) {
				current = temp;
				break;
			}
			if (i == k - 1)
				previous = temp;

			if (i == k - 2)
				beforeprevious = temp;


			i++;
			temp = temp->getPnext();
		}

		if (k == 2)
			this->devices = current;
		else
			beforeprevious->setPnext(current);

		previous->setPnext(current->getPnext());
		current->setPnext(previous);

		return this->devices;
	}
	Household* CopyDevices(Household* Source) {
		if (this->devices == nullptr) {
			this->devices = Source->getDevices();
			return this;
		}

		Device* temp = this->devices;
		Device* head = temp;
		while (temp->getPnext() != nullptr) {
			temp = temp->getPnext();
		}
		temp->setPnext(Source->getDevices());
		this->devices = head;
		return this;
	}
	void input_household() {
		float pprice;
		string psupplier;
		int smeter;
		int nperson;
		cout << "What is the price for one kwh in EUR?\n";
		cin >> pprice;
		setPowerprice(pprice);
		cout << "What is the name of the power supplier?\n";
		cin >> psupplier;
		setPowersupplier(psupplier);
		cout << "How Many Square Meters? ";
		cin >> smeter;
		setSquaremeters(smeter);
		cout << "how many persons?";
		cin >> nperson;
		setNumofpersons(nperson);
		cout << "Is the water heated? (no=n,Yes=y): ";
		char op;
		cin >> op;
		op == 'y' ? setWaterheated(true) : setWaterheated(false);
		setDevices(nullptr);
		Houses.open("House.csv");


	}
	void PrintHousehold(int index) {


		cout << "H O U S E H O L D " << index << " P O W E R   C O N S U M P T I O N \n";
		cout << "---------------------------------------------------------\n";

		cout << setw(global_column) << "Price for one kw/h: " << this->powerPrice << " ct/kWh" << endl;
		cout << setw(global_column) << "Name of the power supplier: " << this->powerSupplier << endl;
		cout << setw(global_column) << "Square Meters: " << this->squaremeters << " qm" << endl;
		cout << setw(global_column) << "Number of persons: " << this->numofpersons << endl;
		cout << setw(global_column) << "Water heated using electricity:" << (this->waterheated ? "Yes" : "No") << endl;
		cout << setw(global_column) << "list of consumers" << endl;
		cout << "---------------------------------------------------------\n";
		int id = 1;
		Device* d = this->devices;
		while (d != NULL) {
			d->print(id, powerPrice);
			cout << "---------------------------------------------------------\n";
			d = d->getPnext();
			id++;
		}
		cout << "---------------------------------------------------------\n";
		cout << setw(global_column) << "Power Consumption square meters:" << this->squaremeters * A << " Kwh" << endl;
		cout << setw(global_column) << "Power Consumption All persons: " << (this->waterheated ? this->numofpersons * W : this->numofpersons * P) << " Kwh" << endl;
		cout << setw(global_column) << "Total Annual power Consumption: " << TotalPower(this) << " kwh" << endl;
		cout << setw(global_column) << "Total Annual power Cost: " << TotalCost(this) << " EUR" << endl;
	}
};


class Address {
private:
	string street = "";
	string no = "";
	string zip = "";
	string city = "";
public:
	Address(string street, string no, string zip, string city) : street(""), no(""), zip(""), city("") {
		this->street = street;
		this->no = no;
		this->zip = zip;
		this->city = city;
	}

	Address() {}
	~Address() {
		if (zip != "") {
			cout << "Address " << to_string() << " at address " << this << "has been deleted\n";
		}

	}

	//getting//
	string getStreet() {
		return street;
	}

	string getNo() {
		return no;
	}

	string getZip() {
		return zip;
	}

	string getCity() {
		return city;
	}

	//setting//

	void setStreet(string value) {
		street = value;
	}
	void setNo(string value) {
		no = value;
	}
	void setZip(string value) {
		zip = value;
	}
	void setCity(string value) {
		city = value;
	}
	void inputAddress() {
		string value;
		cout << "What is the street?";
		cin >> this->street;

		cout << "What is the No?";
		cin >> this->no;


		cout << "What is the Zip?";
		cin >> this->zip;

		cout << "What is the city?";
		cin >> this->city;

	};
	string to_string() {
		return street + ", " + no + ", " + zip + ", " + city;
	}


};


class House {
private:
	int number_of_householods;
	Household** housholds;
	Address address;

public:
	House(int numofhouses, Address add) {
		housholds = new Household * [numofhouses];
		number_of_householods = numofhouses;

		this->address = Address();
		this->address = add;

		for (int i = 0; i < number_of_householods; i++) {
			this->housholds[i] = new Household();
			this->housholds[i]->setDevices(nullptr);
			this->housholds[i]->setNumofpersons(-1);
		}
	}

	House() {}
	~House() {
		for (int i = 0; i < number_of_householods; i++) {
			delete housholds[i];
		}
		delete[] housholds;
		cout << "House at address: " << this << " has been deleted\n";
	}

	Household* get_household(int n) {
		if (n >= 0 && n < number_of_householods) {
			return housholds[n];
		}
		else
			return nullptr;
	}
	Household* operator[](int n) {

		return get_household(n);
	};
	Household* set_household(int n, Household* house) {
		if (n >= 0 && n < number_of_householods) {
			housholds[n] = house;
		}
		return housholds[n];
	}

	void setHouseFromFile(Household** households, Address* address, int numberOfHouseHolds) {
		this->housholds = households;
		this->number_of_householods = numberOfHouseHolds;
		this->address = Address();
		this->address = *address;

	}

	void print_all() {

		for (int n = 0; n < number_of_householods; n++) {
			if (housholds[n]->getNumofpersons() != -1)
				housholds[n]->PrintHousehold(n);
		}

	}


	void PrintHouse_Address() {

		cout << "---------------------------------------------------------\n" <<
			setw(global_column) << "H O U S E" << endl <<
			"---------------------------------------------------------\n";
		cout << setw(global_column) << "(This :" << this << ")" << endl;
		cout << setw(global_column) << "Address :" << this->address.to_string() << endl;
		cout << setw(global_column) << "Number of Households :" << number_of_householods << endl;
		cout << setw(global_column) << "total number of all consumers :" << Consumer::getConsumerCount() << endl;

	}


	void writeDataToFile(string filename, char separator) {
		ofstream file(filename);
		if (!file) {
			cerr << "Error: Unable to open file" << endl;
			return;
		}

		file << "A6" << separator << number_of_householods << separator << address.getStreet() << separator << address.getNo() << separator << address.getZip() << separator << address.getCity() << "\n";

		for (int i = 0; i < number_of_householods; i++) {
			if (this->housholds[i]->getNumofpersons() != -1) {
				file << "Household" << separator << i << separator << (this->housholds[i]->getWaterheated() ? "true" : "false") << separator << this->housholds[i]->getNumofpersons() << separator << this->housholds[i]->getSquaremeters() << separator << this->housholds[i]->getPowerprice() << separator << this->housholds[i]->getPowersupplier() << endl;

				Device* currentDevice = this->housholds[i]->getDevices();
				while (currentDevice != NULL) {
					file << currentDevice->get_string_for_file(separator) << endl;
					currentDevice = currentDevice->getPnext();
				}
			}
		}
		file.close();
	}

	static std::tuple<Household**, Address*, int> ReadDatafromFile(string filename, char separator) {
		ifstream file(filename);
		if (!file) {
			cout << "Error opening file: " << filename << endl;
			return std::make_tuple(new Household * (), new Address(), 0);
		}



		string line;
		string firstLine;
		getline(file, firstLine);

		if (firstLine.empty()) {
			cout << "Empty file" << endl;
			return std::make_tuple(new Household * (), new Address(), 0);
		}


		vector<string> addressData;
		stringstream addressSS(firstLine);
		string addressToken;
		while (getline(addressSS, addressToken, separator)) {
			addressData.push_back(addressToken);
		}


		string street = addressData[2];
		string number = addressData[3];
		string zip = addressData[4];
		string city = addressData[5];

		Address* houseAddress = new Address(street, number, zip, city);


		int num_households = stoi(addressData[1]);

		Household** households = new Household * [num_households];
		for (int i = 0; i < num_households; i++) {
			households[i] = new Household();
			households[i]->setDevices(nullptr);
			households[i]->setNumofpersons(-1);
		}




		int index = 0;

		while (getline(file, line)) {
			if (line.empty()) {
				continue;
			}


			char* context = nullptr;
			char* token = strtok_s(&line[0], &separator, &context);
			vector<string> tokens;
			while (token != nullptr) {
				tokens.push_back(token);
				token = strtok_s(nullptr, &separator, &context);
			}


			if (tokens[0] == "Household") {
				index = stoi(tokens[1]);
				bool isHeated = tokens[2] == "true";
				int numOfPersons = stoi(tokens[3]);
				int squareMeters = stoi(tokens[4]);
				float powerPrice = stof(tokens[5]);
				string powerSupplier = tokens[6];
				households[index] = new Household();
				households[index]->setWaterheated(isHeated);
				households[index]->setNumofpersons(numOfPersons);
				households[index]->setSquaremeters(squareMeters);
				households[index]->setPowerprice(powerPrice);
				households[index]->setPowersupplier(powerSupplier);

			}
			else if (tokens[0] == "Immobile") {

				string ConsumerName = tokens[1];
				int OperatingHours = stoi(tokens[2]);
				string use = tokens[3];
				int watt = stoi(tokens[4]);
				int standByWatt = stoi(tokens[5]);
				Immobile* immobile = new Immobile();
				immobile->setdescription(ConsumerName);
				immobile->setoperating_hours(OperatingHours);
				immobile->setuse(convertStringToEnum(use));
				immobile->setwatt(watt);
				immobile->setwatt_standby(standByWatt);
				households[index]->add_device_to_household(immobile);
			}
			else if (tokens[0] == "Mobile") {

				string ConsumerName = tokens[1];
				float km = stof(tokens[2]);
				string use = tokens[3];
				float watt = stof(tokens[4]);
				Mobile* mobile = new Mobile();
				mobile->setdescription(ConsumerName);
				mobile->setKm(km);
				mobile->setuse(convertStringToEnum(use));
				mobile->setwatt(watt);
				households[index]->add_device_to_household(mobile);
			}
			else if (tokens[0] == "Solar") {

				string ConsumerName = tokens[1];
				int year = stoi(tokens[2]);
				float wattPeak = stof(tokens[3]);
				Solar* solar = new Solar();
				solar->setdescription(ConsumerName);
				solar->setyear_of_installation(year);
				solar->setwatt_peak(wattPeak);
				households[index]->add_device_to_household(solar);
			}
			else {

				cout << "Unknown data type: " << tokens[0] << endl;
			}
		}


		file.close();
		return std::make_tuple(households, houseAddress, num_households);


	}







};



Usage convertStringToEnum(string use) {
	if (use == "daily")
		return daily;
	if (use == "weekly")
		return weekly;
	if (use == "Saturday and Sunday")
		return sa_su;
	if (use == "Monday to Friday")
		return mo_fr;
	if (use == "once")
		return once;

}

string convertEnumToString(Usage use) {
	if (use == daily)
		return "daily";
	if (use == weekly)
		return "weekly";
	if (use == sa_su)
		return "Saturday and Sunday";
	if (use == mo_fr)
		return "Monday to Friday";
	if (use == once)
		return "once";

}
Usage inputUsage(char use) {
	switch (use) {
	case 'o':
		return once;
	case 'd':
		return daily;
	case 'm':
		return mo_fr;
	case 's':
		return sa_su;
	case 'w':
		return weekly;
	default:
		return once;
	}
}



float TotalPower(Household* h) {
	float totalpower = 0;
	float totalpowerconsumers = 0;
	Device* temp = h->getDevices();
	while (temp != NULL) {
		totalpowerconsumers += temp->annual_kWh();
		temp = temp->getPnext();
	}
	if (h->getWaterheated() == true)
		totalpower = (h->getNumofpersons() * W) + (h->getSquaremeters() * A) + totalpowerconsumers;
	else
		totalpower = (h->getNumofpersons() * P) + (h->getSquaremeters() * A) + totalpowerconsumers;

	return totalpower;
}
float TotalCost(Household* h) {

	return TotalPower(h) * h->getPowerprice();
}

float AnnualcostperConsumer(Consumer* c1, Household* h) {
	float costperconsumer;
	costperconsumer = c1->annual_kWh() * h->getPowerprice();
	return costperconsumer;

}

int Consumer::consumerCount = 0;


int main() {
	char seprator;
	string filename;
	int numofhouses;
	House* house = nullptr;
	char userinput;

	while (true) {
		cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE- CLASS VERSION\n"
			"q quit\n"
			"d delete house\n"
			"h house initialisation\n"
			"i Input immobile consumer\n"
			"m input mobile consumer\n"
			"s input solar producer\n"
			"u Move up Device \n"
			"n Input new household\n"
			"c Copy all Devices\n"
			"a Print All Households\n"
			"r read from file\n"
			"w write into file\n"
			"p Print household\n";
		cin >> userinput;

		switch (userinput) {

		case 'q':
			return 0;

		case 'h': {
			cout << "What is the number of housholds?\n";
			cin >> numofhouses;
			cout << "Type in the Address\n";
			Address add = Address();
			add.inputAddress();
			house = new House(numofhouses, add);
			break;
		}

		case 'i': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}

			int numofhouse;
			cout << "what is the number of household to add Immobile consumer to?\n";
			cin >> numofhouse;

			if (house->get_household(numofhouse)->getNumofpersons() == -1) {
				cout << "Household does not exist\n";
				break;
			}

			Immobile* newimmobile = new Immobile;
			newimmobile->input();
			house->get_household(numofhouse)->add_device_to_household(newimmobile);
			break;
		}
		case 's': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}

			int numofhouse;
			cout << "what is the number of household to add Solar producer to?\n";
			cin >> numofhouse;

			if (house->get_household(numofhouse)->getNumofpersons() == -1) {
				cout << "Household does not exist\n";
				break;
			}

			Solar* newsolar = new Solar;
			newsolar->input();
			house->get_household(numofhouse)->add_device_to_household(newsolar);
			break;
		}

		case 'm': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}

			int numofhouse;
			cout << "what is the number of household to add Mobile consumer to?\n";
			cin >> numofhouse;

			if (house->get_household(numofhouse)->getNumofpersons() == -1) {
				cout << "Household does not exist\n";
				break;
			}

			Mobile* newmobile = new Mobile;
			newmobile->input();
			house->get_household(numofhouse)->add_device_to_household(newmobile);
			break;
		}

		case 'n': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}
			int index;
			cout << "What is the number of household to add\n";
			cin >> index;
			house->set_household(index, new Household());
			house->get_household(index)->input_household();
			//he uses the index right away 
			break;
		}

		case'a': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}

			house->PrintHouse_Address();
			house->print_all();
			break;
		}


		case 'p': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}
			int numofhouse;
			cout << "Enter the number of household to print\n";
			cin >> numofhouse;
			house->PrintHouse_Address();
			house->get_household(numofhouse)->PrintHousehold(numofhouse);
			break;
		}

		case 'u': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}
			int numofhouse;
			cout << "Please enter the number of household in which Power Consumer to move\n";
			cin >> numofhouse;
			int k;
			cout << "please enter the number of Power Consumer to move\n";
			cin >> k;

			house->get_household(numofhouse)->MoveUp(k);
			break;
		}

		case'c':
		{

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}
			int source;
			int destination;

			cout << "what is the number of the household to copy from?\n";
			cin >> source;
			cout << "what is the number of household to copy to\n";
			cin >> destination;


			house->get_household(destination)->CopyDevices(house->get_household(source));
			break;



		}
		case 'r': {
			cout << "input file name : ";
			cin >> filename;
			cout << "input the seprator char: ";
			cin >> seprator;
			house = new House();
			Household** households;
			Address* address;
			int number;
			tie(households, address, number) = House::ReadDatafromFile(filename, seprator);
			house->setHouseFromFile(households, address, number);

			break;
		}

		case 'd': {

			house->House::~House();
			house = nullptr;
			break;
		}

		case 'w': {

			if (house == nullptr) {
				cout << "No house has been created yet\n";
				break;
			}
			cout << "input file name : ";
			cin >> filename;
			cout << "input the separator char: ";
			cin >> seprator;
			house->writeDataToFile(filename, seprator);
			cout << "File opened\n";
			cout << "file Closed\n";
			break;
		}
		}
	}






}


