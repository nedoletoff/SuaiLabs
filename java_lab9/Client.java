import java.util.concurrent.TimeUnit;

public class Client {
   int moneyAmount;

   public Client() {
       this.moneyAmount = 0;
   }

   public Client(int moneyAmount) {
       this.moneyAmount= moneyAmount;
   }

    public int getMoneyAmount() {
        return moneyAmount;
    }

    public void setMoneyAmount(int moneyAmount) {
        this.moneyAmount = moneyAmount;
    }

    public void transferMoney(Client other, int transferAmount) throws InterruptedException {
       synchronized (this) {
           //TimeUnit.MICROSECONDS.sleep(100);
           synchronized (other) {
               if (this.getMoneyAmount() >= transferAmount) {
                   other.changeMoneyAmount(transferAmount);
                   this.changeMoneyAmount(-transferAmount);
               }
           }
       }
    }

    @Override
    public String toString() {
        return "" + moneyAmount;
    }

    private void changeMoneyAmount(int delta) {
        this.moneyAmount += delta;
    }
}