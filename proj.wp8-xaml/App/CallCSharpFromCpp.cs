using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.System;
using Microsoft.Phone.Tasks;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Media.PhoneExtensions;
using System.Windows.Media.Imaging;
using System.IO;
using System.IO.IsolatedStorage;

namespace cocos2d
{
    public class CallbackImpl : ICallback
    {
        public CallbackImpl()
        {
            //System.Diagnostics.Debug.WriteLine("in c-sharp constructor");
            BroswerEventHelper.SetCallback(this);
        }

        public void shareGame(String _string)
        {
            ShareLinkTask sharelink = new ShareLinkTask();
            sharelink.Title = _string;
            sharelink.LinkUri = new Uri("http://www.windowsphone.com/s?appid=5cca4c48-3b89-4093-999c-cb01fb8d26a5", UriKind.Absolute);

            sharelink.Show();
            //System.Diagnostics.Debug.WriteLine("Share dc roi!");
        }

        public void rateGame()
        {
            //Launcher.LaunchUriAsync(new Uri("ms-windows-store:reviewapp?appid=5cca4c48-3b89-4093-999c-cb01fb8d26a5"));
        }

        public void sharePhoto(String path)
        {
            System.Diagnostics.Debug.WriteLine("Shared photo!");
            System.Diagnostics.Debug.WriteLine(path);

            Picture picture;
            IsolatedStorageFile isolatedStorageFile = IsolatedStorageFile.GetUserStoreForApplication();

            using (IsolatedStorageFileStream fileStream = isolatedStorageFile.OpenFile(path, FileMode.Open, FileAccess.Read))
            {
                MediaLibrary library = new MediaLibrary();
                picture = library.SavePicture("screenshot.png", fileStream);

                fileStream.Close();
                isolatedStorageFile.DeleteFile(path);
            }

            ShareMediaTask sharephoto = new ShareMediaTask();
            sharephoto.FilePath = picture.GetPath();
            sharephoto.Show();
        }

        public void likePage()
        {
            Windows.System.Launcher.LaunchUriAsync(new Uri("fb:pages?id=280965332027322"));
        }
    }
}
