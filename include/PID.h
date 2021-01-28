class PID { 
private: 
  const double Kp;
  const double Ki;
  const double Kd;

  double integral = 0.0;
  double derivative = 0.0;
  double lastError = 0.0;

  bool integralEnabled = true;
protected:
  double calculateProportional(double error) { 
    return error * Kp;
  }

  double calculateIntegral(double error) {
      integral += error;
      return integral * Ki;
  }

  double calculateDerivative(double error) { 
    derivative = error - lastError;
    lastError = error;
    return derivative * Kd;
  }
public: 
  /**
   * Main constructor for the pid class. If one of the things is not 
   * necessary, for instance if a PD controller is wanted, just pass 
   * the Ki value as 0.0. Google PID Controller for more info on what
   * these do.
   *
   * 
   */
  PID(double Kp, double Ki, double Kd) : Kp(Kp), Ki(Ki), Kd(Kd) { } 

  /**
   * If one were to google `PID Controller` this would be u(x)
   * 
   * @param error the error function to pass (probably should be a linear error function)
   * @returns the value to counteract the error with
   */
  double calculateFromError(double error) {
    if (integralEnabled) {
      return calculateProportional(error) + calculateIntegral(error) + calculateDerivative(error);
    } else {
      return calculateProportional(error) + calculateDerivative(error);
    }
  }

  /**
   * I've heard there are times when the integral isn't wanted
   * to be calculated so this function will enable it if it needs
   * to be calculated at some point, after being disabled.
   */
  void enableIntegral() { 
    setIntegralEnabled(true);
  }

  /**
   * I've heard htere are times when one does not want to 
   * calculate the integral value, I think being at max torque
   * or being a long way away from the goal, because, we don't
   * want the integral value to sky-rocket and dwarf the other terms
   * trying to over exert on some physical component, so this function
   * disables calculating the integral value
   */
  void disableIntegral() { 
    setIntegralEnabled(false);
  }


  void setIntegralEnabled(bool enabled) { 
    integralEnabled = enabled;
  }

  /**
   * Resets the state of the class
   * Doesn't reset the Kp, Ki, Kd values. 
   * Only the state vales of the class.
   * Reset, for example, once some action is 
   * completed, to keep the current integral value
   * from polluting the next one
   */
  void reset() {
    resetIntegral();
    derivative = 0.0;
    lastError = 0.0;
  }

  void resetIntegral() { 
    calc
    integral = 0.0;
  }
};