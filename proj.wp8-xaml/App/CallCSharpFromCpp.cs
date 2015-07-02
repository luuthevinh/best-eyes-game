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
using System.Windows.Threading;
using Windows.ApplicationModel.Store;
using System.Windows;

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
            sharelink.LinkUri = new Uri("http://www.windowsphone.com/s?appid=f2bde5a7-9b1a-4b34-82c3-6b957e6d2da6", UriKind.Absolute);
           
            sharelink.Show();
            //System.Diagnostics.Debug.WriteLine("Share dc roi!");
        }

        public void rateGame()
        {
            Launcher.LaunchUriAsync(new Uri("ms-windows-store:reviewapp?appid=f2bde5a7-9b1a-4b34-82c3-6b957e6d2da6"));
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

        public void showAds(bool isshow)
        {
            if(isshow == true)
            {
                Deployment.Current.Dispatcher.BeginInvoke(() => {
                    MainPage.Current.ShowAds();
                });
            }
            else
            {
                //MainPage.Current.HideAds();
            }
        }

        public void removeAds()
        {
            //UI Thread, RequestProductPurchaseAsync làm trên UI thread
            System.Windows.Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                purchaseAds();
            });
        }

        private async void purchaseAds()
        {
            if (!Windows.ApplicationModel.Store.CurrentApp.LicenseInformation.ProductLicenses["RemoveAds_BestEyes"].IsActive)
            {
                try
                {
                    //ListingInformation li = await Windows.ApplicationModel.Store.CurrentApp.LoadListingInformationAsync();
                    //string pID = li.ProductListings["RemoveAds_BestEyes"].ProductId;

                    await Windows.ApplicationModel.Store.CurrentApp.RequestProductPurchaseAsync("RemoveAds_BestEyes", false);
                }
                catch (Exception ex)
                {
                    //MessageBox.Show(ex.Message);
                }
            }
        }

        public bool isBuyRemoveAds()
        {
            return Windows.ApplicationModel.Store.CurrentApp.LicenseInformation.ProductLicenses["RemoveAds_BestEyes"].IsActive;
        }
    }

}
