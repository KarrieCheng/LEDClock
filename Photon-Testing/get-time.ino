//HI NICK!!!
//Hi

//Upload this code to the Particle Build IDE and flash it onto the Photon to get
//it working.

int led1 = D7;
int h;
int m;

void setup() {
    pinMode(led1, OUTPUT);
    Time.zone(-6);
    Particle.syncTime();
    h = Time.hour();
    m = Time.minute();
    Particle.variable("hour", h);
    Particle.variable("minute", m);
    digitalWrite(led1, LOW);
}

void loop() {
    // The current code turns on the LED at 10:18 AM (I deployed it at 10:17)
    // and turns it off again at 10:19. Hour and minute are being updated properly
    // on the cloud but my HTML request is being silly and not processing.
    //
    // To check the status of the variables paste the following requests
    // into a browser:
    //
    // Hour: https://api.particle.io/v1/devices/37002b000347343138333038/hour?access_token=e3eaafd7eae403adc867a166d5dd34b88935364b
    // Minute: https://api.particle.io/v1/devices/37002b000347343138333038/minute?access_token=e3eaafd7eae403adc867a166d5dd34b88935364b
    
    Particle.syncTime();
    h = Time.hour();
    m = Time.minute();
    if(h == 10 && m == 18){
        digitalWrite(led1, HIGH);
    }
    else{
        digitalWrite(led1, LOW);
    }
}