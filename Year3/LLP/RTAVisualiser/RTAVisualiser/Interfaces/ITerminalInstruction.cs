namespace RTAVisualiser.Interfaces
{
    public interface ITerminalInstruction
    {
        System.Diagnostics.Process Task { get; set; }

        void Launch();
        void SetArguments(string arguments);
    }
}
