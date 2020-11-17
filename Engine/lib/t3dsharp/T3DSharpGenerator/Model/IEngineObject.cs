namespace T3DSharpGenerator.Model
{
    public interface IEngineObject
    {
        string Name { get; set; }
        string ManagedType { get; set; }
        string NativeReturnType { get; set; }
        string NativeArgType { get; set; }
    }
}