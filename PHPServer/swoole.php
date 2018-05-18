<?php

class WebsocketTest {
    public $server;
    public $uid2fd = array();
    public function __construct() {
        $this->server = new swoole_websocket_server("192.168.150.138", 9501);
        $this->server->on('open', function (swoole_websocket_server $server, $request) {
            //建立uid和fd的关系
            $this->uid2fd[$request->get['uid']] = $request->fd;
            echo "用户 {$request->get['uid']}({$request->fd}) 已上线  \n";
        });
        
        $this->server->on('message', function (swoole_websocket_server $server, $frame) {
            $uid = array_search($frame->fd, $this->uid2fd); 
            echo "收到来自 用户 {$uid}({$frame->fd})的数据 :{$frame->data} \n";
            $server->push($frame->fd, "this is server");
        });
        
        $this->server->on('close', function ($ser, $fd) {
            //关闭连接时，释放对应键
            $uid = array_search($fd, $this->uid2fd); 
            if($uid)
            {
                unset($this->uid2fd[$uid]);
            }
            echo "用户{$uid}({$fd})已下线 \n";
            
        });
        
        $this->server->on('request', function ($request, $response) {
            
            //获取通知列表
            $userArr = json_decode($request->post['user']);
            $userArr = is_array($userArr) ? $userArr : array();
            
            //遍历发送消息
            foreach ($userArr as $key => $uid)
            {
                if(array_key_exists($uid, $this->uid2fd))
                {
                    @$this->server->push($this->uid2fd[$uid], $request->post['msg']);
                    echo "已对用户{$uid}({$this->uid2fd[$uid]})发送通知 \n";
                }
                else
                {
                    echo "用户 {$uid} 未上线!\n";
                }
            }
            // 接收http请求从get获取message参数的值，给用户推送
//             foreach ($this->server->connections as $fd) {
//                 @$this->server->push($fd, $request->get['msg']);
//             }
        });
        
        $this->server->start();
    }
}
new WebsocketTest();



?>