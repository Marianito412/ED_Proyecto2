#include <chrono>
#include <iostream>
#include "ClasesProyecto/Operation.h"
#include "ClasesProyecto/OpGenerator.h"
#include "ClasesProyecto/RandomKeyGenerator.h"
#include "ClasesProyecto/RandomTypeGenerator.h"
#include "ClasesProyecto/StaticTypeGenerator.h"
#include "Estructuras/Abstractas/Dictionary.h"
#include "Estructuras/Concretas/AVLTDictionary.h"
#include "Estructuras/Concretas/BSTDictionary.h"
#include "Estructuras/Concretas/HashTable.h"
#include "Estructuras/Concretas/STDictionary.h"
#include "Estructuras/Concretas/UnsortedArrayDictionary.h"
#include "Menu/Helpers.h"
#include "Menu/Menu.h"
#include "Menu/Opciones/Funcion.h"

void LoadDictRandom(Dictionary<int, int>* Dict)
{
    for (int i = 0; i<10000;i++)
    {
        int Random = rand()%1000;
        try
        {
            Dict->insert(Random, Random);    
        }
        catch (...)
        {
        }
        
    }
}

void BenchmarkOperations(OpGenerator* OpGen)
{
    if (OpGen->Dict == nullptr || OpGen->TypeGenerator == nullptr || OpGen->KeyGenerator == nullptr)
    {
        cout<<"No se puede correr el benchmark con la configuración actual.\n"
              "Asegurese de haber escojido Diccionario, Operaciones y Llaves"<<endl;
        return;
    }
    OpGen->Generate();
    List<Operation>* Ops =OpGen->GetOps();
    long long Aggregate = 0;
    long long duration = 0;
    for (Ops->goToStart(); !Ops->atEnd(); Ops->next())
    {
        Operation Op = Ops->getElement();
        if (Op.Op == OpType::Insert)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            try
            {
                OpGen->Dict->insert(Op.Key, Op.Key);
            }
            catch (...)
            {
                continue;
            }
            auto end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        if (Op.Op == OpType::Remove)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            try
            {
                OpGen->Dict->remove(Op.Key);
            }
            catch (...){ }
            auto end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        if (Op.Op == OpType::Find)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            try
            {
                OpGen->Dict->getValue(Op.Key);
            }
            catch (...){}
            auto end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        Aggregate += duration;
    }
    //Finalizar reloj
    std::cout <<Aggregate<<endl;
}

void OperacionesMezcladas(Dictionary<int, int>* Dict)
{
    //Generar operaciones aleatorias
    OpGenerator* OpGen = new OpGenerator(Dict, 10000, new RandomTypeGenerator(), new RandomKeyGenerator());
    OpGen->Generate();
    List<Operation>* Ops =OpGen->GetOps();
    
    //Iniciar reloj luego de generación de operaciones
    auto begin = std::chrono::high_resolution_clock::now();
    for (Ops->goToStart(); Ops->atEnd(); Ops->next())
    {
        Operation Op = Ops->getElement();
        if (Op.Op == OpType::Insert)
        {
            Dict->insert(Op.Key, Op.Key);
        }
        if (Op.Op == OpType::Remove)
        {
            Dict->remove(Op.Key);
        }
        if (Op.Op == OpType::Find)
        {
            Dict->getValue(Op.Key);
        }
    }
    //Finalizar reloj
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<endl;
    delete OpGen;
}

void SelectDictType(OpGenerator* Generator)
{
    List<string>* Dicts = new ArrayList<string>(5);
    Dicts->append("UnsortedArrayDictionary");
    Dicts->append("HashTable");
    Dicts->append("BSTDictionary");
    Dicts->append("AVLDictionary");
    Dicts->append("SplayDictionary");
    bool Cancelado;
    string Resultado;
    Helpers::GetElement(Dicts, Cancelado, Resultado);

    if (Cancelado)
    {
        return;
    }
    delete Generator->Dict;
    if (Resultado == "UnsortedArrayDictionary")
    {
        Generator->Dict = new UnsortedArrayDictionary<int, int>();
    }
    else if (Resultado == "HashTable")
    {
        Generator->Dict = new HashTable<int, int>();
    }
    else if (Resultado == "BSTDictionary")
    {
        Generator->Dict = new BSTDictionary<int, int>();
    }
    else if (Resultado == "AVLDictionary")
    {
        Generator->Dict = new AVLTDictionary<int, int>();
    }
    else if (Resultado == "SplayDictionary")
    {
        Generator->Dict = new STDictionary<int, int>();
    }
    delete Dicts;
    system("cls");
}

void SelectOpType(OpGenerator* Generator)
{
    List<string>* Ops = new ArrayList<string>(5);
    Ops->append("Inserción");
    Ops->append("Borrado");
    Ops->append("Busqueda");
    Ops->append("Operaciones Mezcladas");
    bool Cancelado;
    string Resultado;
    Helpers::GetElement(Ops, Cancelado, Resultado);
    if (Cancelado)
    {
        return;
    }
    delete Generator->TypeGenerator;

    if (Resultado == "Inserción")
    {
        Generator->TypeGenerator = new StaticTypeGenerator(OpType::Insert);
    }
    else if (Resultado == "Borrado")
    {
        Generator->TypeGenerator = new StaticTypeGenerator(OpType::Remove);
        LoadDictRandom(Generator->Dict);
    }
    else if (Resultado == "Busqueda")
    {
        Generator->TypeGenerator = new StaticTypeGenerator(OpType::Find);
        LoadDictRandom(Generator->Dict);
    }
    else if (Resultado == "Operaciones Mezcladas")
    {
        Generator->TypeGenerator = new RandomTypeGenerator();
    }
    system("cls");
}

void SelectKeyGen(OpGenerator* Generator)
{
    List<string>* KeyGens = new ArrayList<string>(5);
    KeyGens->append("Ascendente");
    KeyGens->append("Aleatorio");
    KeyGens->append("Grupos");
    bool Cancelado;
    string Resultado;
    Helpers::GetElement(KeyGens, Cancelado, Resultado);
    if (Cancelado)
    {
        return;
    }
    delete Generator->KeyGenerator;

    if (Resultado == "Ascendente")
    {
        Generator->KeyGenerator = nullptr;
    }
    else if (Resultado == "Aleatorio")
    {
        Generator->KeyGenerator = new RandomKeyGenerator();
    }
    else if (Resultado == "Grupos")
    {
        Generator->KeyGenerator = nullptr;
    }
    delete KeyGens;
    system("cls");
}

int main()
{
    srand(NULL);
    /*
    Dictionary<int, int>* TestDict = new HashTable<int, int>();
    OperacionesMezcladas(TestDict);
    delete TestDict;
    */
    
    Funcion<OpGenerator>* DictTypes = new Funcion<OpGenerator>("Tipo de Diccionario", SelectDictType);
    Funcion<OpGenerator>* OpTypes = new Funcion<OpGenerator>("Tipo de Operaciones", SelectOpType);
    Funcion<OpGenerator>* KeyTypes = new Funcion<OpGenerator>("Tipo de Llaves", SelectKeyGen);
    Funcion<OpGenerator>* Benchmark = new Funcion<OpGenerator>("Correr Benchmark", BenchmarkOperations);
    
    OpGenerator* Generador = new OpGenerator();
    Menu<OpGenerator>* MainMenu = new Menu<OpGenerator>(Generador, "Menu Benchmarks");
    MainMenu->AgregarOpcion(DictTypes);
    MainMenu->AgregarOpcion(OpTypes);
    MainMenu->AgregarOpcion(KeyTypes);
    MainMenu->AgregarOpcion(Benchmark);

    int ResultadoMenu = 0;
    while (ResultadoMenu != -1)
    {
        ResultadoMenu = MainMenu->MostrarMenu();
    }
    delete MainMenu;
    delete Generador;
    
    return 0;
}
