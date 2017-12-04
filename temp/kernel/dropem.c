#include <linux/module.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <linux/tcp.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <net/ip_vs.h>


unsigned int myhook(unsigned int hooknum, struct sk_buff *skb,
										const struct net_device *in,
										const struct net_device *out,
										int (*okfn)(struct sk_buff *))
{
   struct iphdr *iph = ip_hdr(skb);
	if(iph->protocol==6){
		struct tcphdr *tcph = (struct tcphdr *)((char*)iph + iph->ihl * 4);
		if(tcph->dest==htons(1234)){
			//tcph->check = (__sum16)0x1234;
			iph->check =(__sum16)0x1234;
			skb->ip_summed = CHECKSUM_NONE;
			
			}
		}
    return NF_ACCEPT;
}

static struct nf_hook_ops t_hooks[]={
		{
        .hook = myhook,
	 	.hooknum = NF_INET_LOCAL_OUT,
	 	.pf=PF_INET,
	 	.owner = THIS_MODULE,
	 	.priority = NF_IP_PRI_FILTER,
},
	};


static int __init hello_init(void)
{
  int ret;
   ret = nf_register_hooks(t_hooks,sizeof(t_hooks)/sizeof(struct nf_hook_ops));
if(ret<0){
	printk("register hook failed.\n");
	return -1;
}
return 0;
}

static void __exit hello_exit(void)
{
nf_unregister_hooks(t_hooks,sizeof(t_hooks)/sizeof(struct nf_hook_ops));
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");








































