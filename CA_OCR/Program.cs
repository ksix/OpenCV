using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.Net.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Web;
using System.Diagnostics;
/**
* 印刷文字识别WebAPI接口调用示例接口文档(必看)：https://doc.xfyun.cn/rest_api/%E5%8D%B0%E5%88%B7%E6%96%87%E5%AD%97%E8%AF%86%E5%88%AB.html
* 上传图片base64编码后进行urlencode要求base64编码和urlencode后大小不超过4M最短边至少15px，最长边最大4096px支持jpg/png/bmp格式
* (Very Important)创建完webapi应用添加合成服务之后一定要设置ip白名单，找到控制台--我的应用--设置ip白名单，如何设置参考：http://bbs.xfyun.cn/forum.php?mod=viewthread&tid=41891
* 错误码链接：https://www.xfyun.cn/document/error-code (code返回错误码时必看)
* @author iflytek
*/
namespace CA_OCR
{
    class Program
    {
        //public static string imgFile = @"C:\Users\ksig\Pictures\shouxi.png";
        public static string imgFile = @"D:\1112.bmp";

        public static String Md5(string s)
        {
            System.Security.Cryptography.MD5 md5 = new System.Security.Cryptography.MD5CryptoServiceProvider();
            byte[] bytes = System.Text.Encoding.UTF8.GetBytes(s);
            bytes = md5.ComputeHash(bytes);
            md5.Clear();
            string ret = "";
            for (int i = 0; i < bytes.Length; i++)
            {
                ret += Convert.ToString(bytes[i], 16).PadLeft(2, '0');
            }
            return ret.PadLeft(32, '0');
        }

        public static void Headers()
        {
            //  应用ID (必须为webapi类型应用，并印刷文字识别服务，参考帖子如何创建一个webapi应用：http://bbs.xfyun.cn/forum.php?mod=viewthread&tid=36481)
            string x_appid = "600e346f";
            //  接口密钥(webapi类型应用开通印刷文字识别服务后，控制台--我的应用---印刷文字识别---服务的apikey)
            string api_key = "5c40a72a43c28ef35918faddb309ef96";
            //  上传图片路径
            string path = imgFile;
            //  设置语言类型和是否返回文件位置信息
            string param = "{\"language\":\"cn|en\",\"location\":\"true\"}";

            System.Text.Encoding encode = System.Text.Encoding.ASCII;
            byte[] bytedata = encode.GetBytes(param);
            string x_param = Convert.ToBase64String(bytedata);


            TimeSpan ts = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            string curTime = Convert.ToInt64(ts.TotalSeconds).ToString();

            MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
            string result = string.Format("{0}{1}{2}", api_key, curTime, x_param);
            //Console.WriteLine(Program.Md5(x_param));
            string X_checksum = Program.Md5(result);
            //Console.WriteLine(X_checksum);

            byte[] arr = File.ReadAllBytes(path);
            string cc = Convert.ToBase64String(arr);
            string data = "image=" + cc;
            // 印刷文字识别  webapi接口地址
            string Url = "http://webapi.xfyun.cn/v1/service/v1/ocr/general";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(Url);
            request.Method = "POST";
            // 组装http请求头
            request.ContentType = "application/x-www-form-urlencoded";
            request.Headers["X-Appid"] = x_appid;
            request.Headers["X-CurTime"] = curTime;
            request.Headers["X-Param"] = x_param;
            request.Headers["X-CheckSum"] = X_checksum;

            request.ContentLength = Encoding.UTF8.GetByteCount(data);
            Stream requestStream = request.GetRequestStream();
            StreamWriter streamWriter = new StreamWriter(requestStream, Encoding.GetEncoding("gb2312"));
            streamWriter.Write(data);
            streamWriter.Close();

            string htmlStr = string.Empty;
            HttpWebResponse response = request.GetResponse() as HttpWebResponse;
            Stream responseStream = response.GetResponseStream();
            using (StreamReader reader = new StreamReader(responseStream, Encoding.GetEncoding("UTF-8")))
            {
                htmlStr = reader.ReadToEnd();
            }
            responseStream.Close();

            Console.WriteLine(htmlStr);
            //Console.ReadLine();

        }

        static void Main(string[] args)
        {
            DateTime dt1 = DateTime.Now;
            Headers();
            DateTime dt2 = DateTime.Now;
            Console.WriteLine("Xunfei used {0} ms", (dt2 - dt1).TotalMilliseconds);
            DateTime dt3 = DateTime.Now;
            BaiduApi();
            DateTime dt4 = DateTime.Now;
            Console.WriteLine("Baidu used {0} ms", (dt4 - dt3).TotalMilliseconds);
            Console.ReadKey();
        }

        private static string appId = "23588751";
        private static string apiKey = "62puzqNdwyMEsCUAzDDl3Vns";
        private static string secretKey = "5tMCBVxsidnEv55OcqOGvZSdKakFpRMg";

        public static void BaiduApi()
        {
            string url = @"https://aip.baidubce.com/rest/2.0/ocr/v1/accurate?access_token=" + GetAccessToken();
            string imgPath = imgFile;
            byte[] imgBuffer = File.ReadAllBytes(imgPath);
            string imgBase64Str = Convert.ToBase64String(imgBuffer);
            string postData = "image=" + HttpUtility.UrlEncode(imgBase64Str);
            HttpPost(url, postData);
        }

        public static String GetAccessToken()
        {
            String authHost = "https://aip.baidubce.com/oauth/2.0/token";
            HttpClient client = new HttpClient();
            List<KeyValuePair<String, String>> paraList = new List<KeyValuePair<string, string>>();
            paraList.Add(new KeyValuePair<string, string>("grant_type", "client_credentials"));
            paraList.Add(new KeyValuePair<string, string>("client_id", apiKey));
            paraList.Add(new KeyValuePair<string, string>("client_secret", secretKey));
            HttpResponseMessage response = client.PostAsync(authHost, new FormUrlEncodedContent(paraList)).Result;
            String result = response.Content.ReadAsStringAsync().Result;
            JObject json = JObject.Parse(result);
            result = json["access_token"].Value<string>();
            return result;
        }

        public static void HttpPost(string url, string body)
        {
            Encoding encoding = Encoding.UTF8;
            HttpWebRequest request = WebRequest.Create(url) as HttpWebRequest;
            request.Method = "POST";
            request.Accept = "text/html, application/xhtml+xml, */*";
            //request.ContentType = "application/json";
            request.ContentType = "application/x-www-form-urlencoded";
            byte[] buffer = encoding.GetBytes(body);
            request.ContentLength = buffer.Length;
            request.GetRequestStream().Write(buffer, 0, buffer.Length);
            HttpWebResponse response = request.GetResponse() as HttpWebResponse;
            StreamReader sr = new StreamReader(response.GetResponseStream(), Encoding.UTF8);

            string data = sr.ReadToEnd();
            data = JsonConvert.SerializeObject(JObject.Parse(data));
            Console.WriteLine(data);
            //Console.ReadKey();
        }
    }
}
