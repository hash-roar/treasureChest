### overshadow
盒阴影

### linear-gradient
渐变
[获得路径值](https://bennettfeely.com/clippy/)

###  conic-gradient
角向渐变
### clip-path
区域内部分显示


## css的方位与排序

writing-mode：定义了文本水平或垂直排布以及在块级元素中文本的行进方向。
direction：设置文本排列的方向。 rtl 表示从右到左 (类似希伯来语或阿拉伯语)， ltr 表示从左到右。
unicode-bidi：它与 direction 非常类似，两个会经常一起出现。在现代计算机应用中，最常用来处理双向文字的算法是Unicode 双向算法。而 unicode-bidi 这个属性是用来重写这个算法的。


### 绘制三角形

	div {
	  border-top: 50px solid yellowgreen;
	  border-bottom: 50px solid deeppink;
	  border-left: 50px solid bisque;
	  border-right: 50px solid chocolate;
	}
	border-top: 50px solid yellowgreen;
            border-bottom: transparent;
            border-left: transparent;
            border-right: transparent;
    	用渐变绘制:
    	 width: 100px;
	  height: 100px;
	  background: linear-gradient(45deg, deeppink, deeppink 50%, yellowgreen 50%, yellowgreen 100%);
    	旋转:
    	.triangle {
	    width: 141px;
	    height: 100px;
	    position: relative;
	    overflow: hidden;
	    
	    &::before {
	        content: "";
	        position: absolute;
	        top: 0;
	        left: 0;
	        right: 0;
	        bottom: 0;
	        background: deeppink;
	        transform-origin: left bottom;
	        transform: rotate(45deg);
	    }
	}