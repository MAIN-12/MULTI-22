#include <BlynkHandler.h>
void CMain(void *parameter)
{
    const TickType_t MAIN_DELAY = 100 / portTICK_PERIOD_MS;
    for (;;)
    {
        // Pump.Main();
        vTaskDelay(MAIN_DELAY);
    }
}

void cRUN(void *parameter)
{
    const TickType_t RUN_DELAY = 10 / portTICK_PERIOD_MS;
    for (;;)
    {
        // Pump.Run();
        vTaskDelay(RUN_DELAY);
    }
}

void BlynkUpdate(void *parameter)
{
    const TickType_t BLYNK_DELAY = 1000 / portTICK_PERIOD_MS;
    for (;;)
    {
        BlynkEdgent.run();
        timer.run();
        vTaskDelay(BLYNK_DELAY);
    }
}

void MultiTreadStart()
{
    // xTaskCreate(CMain, "C_MAIN", 10000, NULL, 20, NULL);
    // xTaskCreatePinnedToCore(cRUN, "C_RUN", 10000, NULL, 25, NULL, CONFIG_ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(BlynkUpdate, "BLYNK_UPDATE", 10000, NULL, 10, NULL, CONFIG_ARDUINO_RUNNING_CORE);
    // xTaskCreate(LogTask, "LOG_CHECK", 2000, NULL, 1, NULL);
    // xTaskCreate(ParametersUpdate, "PARAMETERS_UPDATE", 4000, NULL, 1, NULL);
}