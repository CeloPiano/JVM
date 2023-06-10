import java.util.*;
import java.util.stream.Collectors;

public class maluco implements MinhaInterface {
    public static void main(String[] args) {
        maluco complexo = new maluco();

        complexo.metodoInterface(); // Chamada do método da interface
    }

    @Override
    public void metodoInterface() {
        System.out.println("Implementação do método da interface");
    }
    static interface MinhaInterface {
        void metodoInterface();
    }


    public static void exemploMetodo() {
        List<Pessoa> pessoas = Arrays.asList(
                new Pessoa("Alice", 25),
                new Pessoa("Bob", 30),
                new Pessoa("Carol", 40),
                new Pessoa("David", 35),
                new Pessoa("Eva", 28)
        );

        // Filtrando pessoas com idade superior a 30 e armazenando em uma nova lista
        List<Pessoa> pessoasFiltradas = pessoas.stream()
                .filter(p -> p.getIdade() > 30)
                .collect(Collectors.toList());

        // Ordenando as pessoas por ordem decrescente de idade
        Collections.sort(pessoasFiltradas, Comparator.comparing(Pessoa::getIdade).reversed());

        // Imprimindo as informações das pessoas filtradas e ordenadas
        pessoasFiltradas.forEach(p -> System.out.println(p.getNome() + " - " + p.getIdade()));
    }

    static abstract class Animal {
        protected String nome;

        public Animal(String nome) {
            this.nome = nome;
        }

        public abstract void emitirSom();
    }

    static class Gato extends Animal {
        public Gato(String nome) {
            super(nome);
        }

        public void emitirSom() {
            System.out.println(nome + " está miando...");
        }
    }

    static class Pessoa {
        private String nome;
        private int idade;

        public Pessoa(String nome, int idade) {
            this.nome = nome;
            this.idade = idade;
        }

        public String getNome() {
            return nome;
        }

        public int getIdade() {
            return idade;
        }
    }
}
