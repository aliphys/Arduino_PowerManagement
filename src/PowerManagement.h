
#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H 

#include <Arduino.h>
#include "Board.h"
#include "Battery.h"
#include "Charger.h"
#include <Arduino_PF1550.h>



class PowerManagement{
    public: 
        /**
         * @brief constructor for the PowerManagement 
         */
        PowerManagement();

        /**
         * @brief destructor for the PowerManagement 
         */
        ~PowerManagement();

        /**
         * @brief start communication with the PMIC chip and the power gauge. 
         * @returns true if the initialization was successful, false otherwise
        */
        bool begin();
        
        // TODO: Improve documentation e.g. explain what to do with the returned object
        // I'd avoid to talk about pointers here, since the user doesn't need to know about them        
        /**
         * @brief returns the initialised instance of the Board class
         * @returns the dereferenced board pointer (actual Board instance)
        */
        Board getBoard();
        
        // TODO: Improve documentation e.g. explain what to do with the returned object
        // I'd avoid to talk about pointers here, since the user doesn't need to know about them
        /**
         * @brief returns the initialised instance of the Battery class
         * @returns the dereferenced battery pointer (actual Battery instance)
        */
        Battery getBattery();
        
        // TODO: Improve documentation e.g. explain what to do with the returned object
        // I'd avoid to talk about pointers here, since the user doesn't need to know about them
        /** 
         * @brief returns the initialised instance of the Charger class
         * @returns the dereferenced charger pointer (actual Charger instance)
         */
        Charger getCharger();

    private:
        Battery * battery;
        Board * board;
        Charger * charger;
        PF1550 * pPMIC;
};




#endif