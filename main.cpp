#include "main.h"
using namespace std;

char output[MAX_DATA_LENGTH]; //MAX_DATA_LENGTH fra .h-filen
char port[] = "\\\\.\\COM10"; //com-port konfigurering
char incoming[MAX_DATA_LENGTH];

Morser testSender;
char* testSenderAllAttrPtr;
const uint8_t* messPtr = nullptr;

bool rData = 0;

int main()
{
    system("Color 0A");

    int i = 0;

    char selection = 0;
    char comSelect = 10;
    int speed = 8; //8 er 1 i sekundet
    string message = "message here";
    int lowIntensity = 4;
    int highIntensity = 24;
    string allAttributes;
    string tCommand;

    char ledOn[21] = "14 170 170 170 160 0";

    int tSpeed = 0; //test speed

    testSender.setSpeed(speed); //her bliver standard værdier sat til Morser objekt
    testSender.setMessage(message);
    testSender.setOffIntensity(lowIntensity);
    testSender.setOnIntensity(highIntensity);

    tSpeed = testSender.getSpeed(); //til at teste preset speed fx.

    //cout << "choose COM-port: ";
    //cin >> comSelect;
    //port[7] = comSelect;

    do
    {
        system("CLS");
        cout << "  ____________________________________" << endl;
        cout << " |       JUNO Communication 0.6       |" << endl;
        cout << " |          COM-port: 10              |" << endl;
//        cout << " |               COM-port:  " << comSelect << "         |" << endl;
        cout << " |____________________________________|" << endl;
        cout << "\n";
        cout << "  ------------------------------- Current Values: \n";
        cout << "  1.  Select speed                " << speed << endl;
        cout << "  2.  Select message              " << message << endl;
        cout << "  3.  Select intensity            " << lowIntensity << "  " << highIntensity << endl;
        cout << "  4.  Turn on LED" << endl;
        cout << "  5.  Turn off LED" << endl;
        cout << "  6.  Change COM-Port\n";
        cout << "  7.  Update attributes\n";
        cout << "\n";
        cout << "  8.  Exit\n";
        cout << "\n";
        cout << "  * 9.  Test area\n";
        cout << "  * 0.  Test area 2\n";
        cout << "  ------------------------------------\n";
        cout << "  Enter your selection: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case '1':
            system("CLS");
            cout << "Select speed:\n";
            cout << "Range from 1-31, 8 is once per second\n";

            cin >> speed; 
            testSender.setSpeed(speed);

            cout << "\n";
            break;

        case '2':
            system("CLS");
            cout << "Select message:\n";

            getline(cin >> ws, message); //remove whitespace for blank spaces in message
            testSender.setMessage(message);

            cout << "\n";
            break;

        case '3':
            system("CLS");
            cout << "Select low intensity:\n";
            cout << "Range from 1-31\n";
                
            cin >> lowIntensity;
            testSender.setOffIntensity(lowIntensity);
            
            cout << "\n";
            
            cout << "Select high intensity:\n";
            cout << "Range from 1-31\n";
            
            cin >> highIntensity;
            testSender.setOnIntensity(highIntensity);
            
            cout << "\n";

                //here we check if intensity values are correct, low should be lower than high
                while (lowIntensity > highIntensity) { 
                    cout << "Intensity values are not corret, try again\n";
                    cout << "Select low intensity:\n";
                    cin >> lowIntensity;
                    testSender.setOffIntensity(lowIntensity);
                    cout << "\n";
                    cout << "Select high intensity:\n";
                    testSender.setOnIntensity(highIntensity);
                    cin >> highIntensity;
                    cout << "\n";
                }
            break;
        
        case '4':
            system("CLS");

            cout << "Turning LED on...\n\n";

            toggleArdLED();

            break;

        case '5':
            system("CLS");

            cout << "Turning LED off...\n\n";

            toggleArdLED();

            break;

        case '6':
            system("CLS");

            cout << "choose COM-port: ";
            cin >> comSelect;
            port[7] = comSelect;

            break;

        case '7':
            system("CLS");

            //allAttributes = to_string(speed) + message + to_string(lowIntensity) + to_string(highIntensity);

            cout << "Connecting to Arduino...\n" << endl;

            toArd(); //allAttributes

            break;

        case '8':
            system("CLS");

            cout << "Goodbye.\n";
            Sleep(2000);
            exit(1);
            break;

        case '9':
            cout << "Test area\n";

            testSender.getAllAttrPtr(testSenderAllAttrPtr);

            cout << endl << endl << "All data sent (as wrong int):  " << (int*)testSenderAllAttrPtr << endl;

            cout << endl << endl << "Arduino will receive: " << endl;
            for (unsigned int i = 0; testSenderAllAttrPtr[i] != 0; i++)
            {
                cout << "  0b"; //til at skrive det pænt op, 0b kommer ikke videre til Arduino
                for (uint8_t j = 0; j < 8; j++) {
                    cout << ((testSenderAllAttrPtr[i] & (0b10000000 >> j)) ? '1' : '0');
                }
            }
            cout << "  0b00000000";

            Sleep(5000);

        case '0':

            //testSender.getAllAttrPtr(testSenderAllAttrPtr);

            cout << "Test send to Arduino: ";
            cin >> tCommand;

            //intToArd(tCommand);

            break;


        default: cout << selection << " is not a valid menu item.\n";

            cout << endl;
        }

    } while (selection != 10);

    return 0;
}

int toArd() { //string command

    SerialPort arduino(port);
//    arduino.writeSerialPort(to_send)

    if (arduino.isConnected()) {
        cout << "Connection established to Arduino\n" << endl;
    }
    else {
        cout << "Error in port name\n" << endl;
    }
    //while (arduino.isConnected()) {
        //string command;
        //cout << "Besked til Arduino:\n";
        //cin >> command;
        //}
    /*
        char* charArray = new char[command.size() + 1];
        copy(command.begin(), command.end(), charArray);
        charArray[command.size()] = '\n';
        */

        testSender.getAllAttrPtr(testSenderAllAttrPtr);
        
        for (unsigned int i = 0; testSenderAllAttrPtr[i] != 0; i++)
        {
            cout << "sent byte nr. " << i << ": " << (char)testSenderAllAttrPtr[i] << " (as int: " << (int)testSenderAllAttrPtr[i] << ")" << endl;
            //arduino.writeSerialPort((char*)testSenderAllAttrPtr[i], MAX_DATA_LENGTH);
            //arduino.writeSerialPort(testSenderAllAttrPtr, MAX_DATA_LENGTH);
        }

        int fi = 0;

        for (fi = 0; testSenderAllAttrPtr[fi] != 0b00000000; fi++)
        {

        }

        arduino.writeSerialPort(testSenderAllAttrPtr, fi+1);
        arduino.readSerialPort(output, MAX_DATA_LENGTH);

        cout << "\nArduino Output (if any): " << output << endl; //output fra Arduino bliver cout'et her, måske ikke nødvendigt

        cout << "\nAttributes updated to Arduino!" << endl;

        //delete[] charArray;

        Sleep(5000);    

    return 0;
}

int toggleArdLED()
{
    string command;
    SerialPort arduino(port);
    if (arduino.isConnected()) {
        cout << "Connection established to Arduino\n" << endl;
    }
    else {
        cout << "Error in port name\n" << endl;
    }

    /*
    while (arduino.isConnected())
    {
        cout << "Test send to Arduino: ";
        cin >> command;
    }
    */

    char* charArray = new char[command.size() + 1];
    copy(command.begin(), command.end(), charArray);
    charArray[command.size()] = '\n';

    char ledToggle[6] = { 14,170,170,170,160,0 };

    arduino.writeSerialPort(ledToggle, 6);

    arduino.readSerialPort(output, MAX_DATA_LENGTH);

    //cout << "sent command: " << command << endl;
    cout << "arduino output: " << output << endl;

    delete[] charArray;

    Sleep(1000);

    return 0;
}