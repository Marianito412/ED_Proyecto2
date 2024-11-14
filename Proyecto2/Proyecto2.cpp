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
#include "ClasesProyecto/AscendingKeyGenerator.h"
#include "Menu/Helpers.h"
#include "Menu/Menu.h"
#include "Menu/Opciones/Funcion.h"
#include "ClasesProyecto/GroupKeyGenerator.h"

/*
 * Esta función se encarga de utilizar el generador creado, procesar las operaciones y medir el tiempo. Es básciamente el main
 * Autor: Mariano Soto
 */

void BenchmarkOperations(OpGenerator* OpGen)
{
    if (OpGen->Dict == nullptr || OpGen->TypeGenerator == nullptr || OpGen->KeyGenerator == nullptr)
    {
        cout<<"No se puede correr el benchmark con la configuración actual.\n"
              "Asegurese de haber escojido Diccionario, Operaciones y Llaves"<<endl;
        return;
    }
    OpGen->TypeGenerator->Reset();
    OpGen->KeyGenerator->Reset();
    
    OpGen->Generate();
    List<Operation>* Ops =OpGen->GetOps();
    long long duration = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    for (Ops->goToStart(); !Ops->atEnd(); Ops->next())
    {
        Operation Op = Ops->getElement();
        if (Op.Op == OpType::Insert)
        {
            try
            {
                OpGen->Dict->insert(Op.Key, Op.Key);
            }
            catch (...){ }
        }
        if (Op.Op == OpType::Remove)
        {
            try
            {
                OpGen->Dict->remove(Op.Key);
            }
            catch (...){ }
        }
        if (Op.Op == OpType::Find)
        {
            try
            {
                OpGen->Dict->contains(Op.Key);
            }
            catch (...){}
        }
    }
    //Finalizar reloj
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout <<duration<<endl;
}

void LoadDictRandom(Dictionary<int, int>* Dict)
{
    for (int i = 0; i<10000;i++)
    {
        int Random = rand()%10000;
        try
        {
            Dict->insert(Random, Random);    
        }
        catch (...)
        {
        }
    }
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
        Generator->KeyGenerator = new AscendingKeyGenerator();
    }
    else if (Resultado == "Aleatorio")
    {
        Generator->KeyGenerator = new RandomKeyGenerator();
    }
    else if (Resultado == "Grupos")
    {
        Generator->KeyGenerator = new GroupKeyGenerator();
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
