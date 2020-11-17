using System.Collections.Generic;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Util
{
    public class SimObjectTree
    {
        public static List<EngineClass> BuildAsList(List<EngineClass> classes) {
            Dictionary<IEngineObject, List<EngineClass>> subclassDictionary =
                new Dictionary<IEngineObject, List<EngineClass>>();
            Dictionary<string, EngineClass> classNameDictionary = new Dictionary<string, EngineClass>();

            // Create a mapping from classname to class objects
            classes.ForEach(x => classNameDictionary[x.Name] = x);

            classes.ForEach(x => {
                // First, filter out non-simclasses
                if (x.SuperType == null) return;
                // Insert the current simclass as a subclass to the parent
                if (!subclassDictionary.ContainsKey(x.SuperType)) {
                    subclassDictionary[x.SuperType] = new List<EngineClass>();
                }

                subclassDictionary[x.SuperType].Add(x);
            });

            List<EngineClass> simClasses = new List<EngineClass>();

            // Locate the top-level class
            EngineClass simObjectClass = classes.Find(x => x.Name == "SimObject");

            // Insert all sim classes into the simClasses list
            AddClassAndSubclasses(subclassDictionary, simClasses, simObjectClass);
            return simClasses;
        }

        private static void AddClassAndSubclasses(Dictionary<IEngineObject, List<EngineClass>> subclassDictionary,
            List<EngineClass> simClasses, EngineClass simObjectClass, bool isDatablock = false) {
            simObjectClass.IsDatablock = isDatablock;
            simObjectClass.IsSimObject = true;

            // Add this class to the simClasses
            simClasses.Add(simObjectClass);
            // If this class has no subclasses, return
            if (!subclassDictionary.ContainsKey(simObjectClass)) return;
            // Add the class and all subclasses
            subclassDictionary[simObjectClass].ForEach(x =>
                AddClassAndSubclasses(subclassDictionary, simClasses, x, isDatablock || x.Name == "SimDataBlock"));
        }
    }
}