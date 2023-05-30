
interface animals_actions {
    public void animal_sound();
    public void animal_run();
};  

abstract class animal {
    public String cor_pelo;    

};  

class lion extends animal implements animals_actions{
    
    public lion(String cor_pelo){
        super.cor_pelo = cor_pelo;
    };
    
    public void animal_sound(){
        System.out.println("ROAARRR!");
    }
    
    public void animal_run(){
        System.out.println("leão correndo.");
    }
    
}

class cat extends animal implements animals_actions{
    
    public cat(String cor_pelo){
        super.cor_pelo = cor_pelo;
    };
    
    public void animal_sound(){
        System.out.println("MIAUUUU!");
    }

    public void animal_run(){
        System.out.println("gato andando.");
    }

}


public class zoo {

    static {int x = 10; System.out.println("Dentro do bloco estático animal!");};

    String nome_zelador = "José"; 
    int idade_zelador = 72;
    double altura_zelador = 1.75;

    public static void main(String[] args){
        String cor_pelo_gatinho = "azul";
        String cor_pelo_leao = "preto";

        cat gatinho = new cat(cor_pelo_gatinho);
        lion leao = new lion(cor_pelo_leao);

        gatinho.animal_sound();
        leao.animal_sound();

        System.out.println("cor pelo leao = " + leao.cor_pelo);
        System.out.println("cor pelo gato = " + gatinho.cor_pelo);
    };

}