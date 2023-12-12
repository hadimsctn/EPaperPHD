namespace EPaperPHD.Model
{
    public class Folder
    {
        public string Name { get; set; }
        public List<Folder> Subfolders { get; set; }

        public Folder(string name)
        {
            Name = name;
            Subfolders = new List<Folder>();
        }
    }
}
